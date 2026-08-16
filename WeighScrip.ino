#include "FS.h"
#include "src/ui.h"
#include "src/actions.h"
#include "src/screens.h"
#include "src/vars.h"

#include "structures.h"
#include "time.h"

#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

//#include <pthread.h>

// ВАЖНО: LVGL обходит дерево виджетов рекурсивно (layout + отрисовка).
// Стек loopTask в Arduino-ESP32 по умолчанию всего 8 КБ, и на глубоких
// экранах (напр. редактор пресетов) его не хватает ->
// "Stack canary watchpoint triggered (loopTask)".
// Макрос должен стоять именно в глобальной области .ino-файла.
SET_LOOP_TASK_STACK_SIZE(32 * 1024);

//because screen is rotated, this way easier
#define TFT_HOR_RES TFT_HEIGHT
#define TFT_VER_RES TFT_WIDTH
//#define DRAW_BUF_SIZE (TFT_WIDTH * TFT_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
#define DRAW_BUF_SIZE (320 * 20)


TFT_eSPI tft = TFT_eSPI();
SPIClass touchscreenSpi = SPIClass(VSPI);

XPT2046_Touchscreen touchscreen(TOUCH_CS);
uint16_t touchscreenMinX = 200, touchscreenMaxX = 3700, touchscreenMinY = 240, touchscreenMaxY = 3800;

lv_indev_t *indev;
uint8_t *draw_buf;
uint32_t lastTick = 0;

//pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;


void setup() {
  Serial.begin(115200);

  tft.init();
  tft.fillScreen(TFT_GREEN);

  touchscreenSpi.begin(TFT_SCLK, TFT_MISO, TFT_MOSI, TOUCH_CS);
  touchscreen.begin(touchscreenSpi);
  touchscreen.setRotation(3);

  lv_init();
  draw_buf = new uint8_t[DRAW_BUF_SIZE];
  lv_display_t *disp;
  disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, DRAW_BUF_SIZE);
  
  indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, read_touch);

  // Serial.println("[BOOT] ui_init() ->");
  // show_lvgl_mem_info("before ui_init");
  ui_init();
  // Serial.println("[BOOT] ui_init() <- ok");
  // show_lvgl_mem_info("after ui_init");

  tft.setRotation(3);

  change_to_main_screen();
  // Serial.println("[BOOT] first screen loaded");

  init_SD();
  Serial.print(get_test_string_sd());
  //load_presets_from_SD();

  // struct paramPresetStruct *myPreset;
  // for (int i = 0; i < get_var_cur_preset_amount(); i++) {
  //   myPreset = get_preset(i);
  //   Serial.println(myPreset -> name);
  // }

  // uint32_t ide_flash_size = ESP.getFlashChipSize();
  // Serial.printf("Configured IDE Flash Size: %d MB\n", ide_flash_size / (1024 * 1024));

  init_wifi();

  init_time();
}

void loop() {
  lv_loop();

  wifi_tick();   // следит за связью, не блокирует

  //get_debug_info(0, 0, 1);

  delay(10);
}


void lv_loop() {
  lv_tick_inc(millis() - lastTick);
  lastTick = millis();

  // Трассировка первых кадров: если в мониторе будет "frame N ->" без "<- ok",
  // значит зависли ВНУТРИ lv_timer_handler (отрисовка/layout), а не в нашем коде.
  static uint32_t lvFrame = 0;
  bool trace = (lvFrame < 20);
  if (trace) {
    Serial.printf("[LV] frame %u ->\n", (unsigned)lvFrame); Serial.flush();
    if (lvFrame < 4) show_lvgl_mem_info("before frame");
  }

  lv_timer_handler();

  if (trace) { Serial.printf("[LV] frame %u <- ok\n", (unsigned)lvFrame); Serial.flush(); }
  lvFrame++;
  //lv_timer_periodic_handler();
  // pthread_mutex_lock(&my_mutex);
  // lv_task_handler();
  // pthread_mutex_unlock(&my_mutex);
  
  wifi_tick();
  ui_tick();
}

void read_touch(lv_indev_t *indev, lv_indev_data_t *data) {
  if (!touchscreen.touched()) {
    data -> state = LV_INDEV_STATE_RELEASED;
    return;
  }

  TS_Point p = touchscreen.getPoint();
  if (p.x < touchscreenMinX) touchscreenMinX = p.x;
  if (p.x > touchscreenMaxX) touchscreenMaxX = p.x;
  if (p.y < touchscreenMinY) touchscreenMinY = p.y;
  if (p.y > touchscreenMaxY) touchscreenMaxY = p.y;

  // min and max on X are changed, because the touch is mirrored, and that helps
  data -> point.x = map(p.x, touchscreenMaxX, touchscreenMinX, 1, TFT_HOR_RES);
  data -> point.y = map(p.y, touchscreenMinY, touchscreenMaxY, 1, TFT_VER_RES);
  data -> state = LV_INDEV_STATE_PRESSED;
}
