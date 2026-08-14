void get_debug_info(bool heapInf, bool flasshInf, bool looptask) {
  //Serial.println("========================================");

  if (heapInf)
  {
    show_heap_info();
  }

  if (flasshInf)
  {
    show_flash_inf();
  }

  if (looptask) {
    show_looptask_info();
  }
}

void show_heap_info() {
  Serial.printf("8BIT: %d", heap_caps_get_free_size(MALLOC_CAP_8BIT));
  Serial.println();
  Serial.printf("32BIT: %d", heap_caps_get_free_size(MALLOC_CAP_32BIT));
  Serial.println();
  Serial.printf("DMA: %d", heap_caps_get_free_size(MALLOC_CAP_DMA));
  Serial.println();
  Serial.printf("SPIRAM: %d", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
  Serial.println();
}

void show_flash_inf() {

}

void show_looptask_info() {
  // временная диагностика: следим за запасом стека loopTask
  static uint32_t lastStackLog = 0;
  if (millis() - lastStackLog > 2000) {
    lastStackLog = millis();
    show_stack_info("loop");
  }
}

// Сколько байт стека у текущей задачи ОСТАЛОСЬ в самый худший момент.
// Если значение падает к нулю - будет "Stack canary watchpoint triggered".
void show_stack_info(const char* tag) {
  // В ESP-IDF (в отличие от «ванильного» FreeRTOS) эта функция возвращает
  // уже БАЙТЫ, а не слова. Умножать на 4 не нужно.
  UBaseType_t freeBytes = uxTaskGetStackHighWaterMark(NULL);
  Serial.printf("[STACK] %-24s free: %u bytes\n", tag, (unsigned)freeBytes);
}

// Состояние ВНУТРЕННЕЙ кучи LVGL (это не общая куча ESP32!).
// Если used_pct подбирается к 100 - LV_MEM_SIZE в lv_conf.h мал.
void show_lvgl_mem_info(const char* tag) {
  static bool once = false;
  if (!once) {
    once = true;
    Serial.printf("[LVGL]  version %d.%d.%d\n",
                  LVGL_VERSION_MAJOR, LVGL_VERSION_MINOR, LVGL_VERSION_PATCH);
#ifdef LV_MEM_SIZE
    Serial.printf("[LVGL]  LV_MEM_SIZE = %u B\n", (unsigned)LV_MEM_SIZE);
#else
    Serial.println("[LVGL]  LV_MEM_SIZE not defined here");
#endif
  }

  // lv_mem_monitor() есть всегда; если LVGL работает через clib malloc,
  // total_size вернётся нулём - тогда смотрим на [HEAP].
  lv_mem_monitor_t mon;
  lv_mem_monitor(&mon);
  Serial.printf("[LVMEM] %-18s total: %u B  used: %u%%  free: %u B  biggest: %u B  frag: %u%%\n",
                tag, (unsigned)mon.total_size, (unsigned)mon.used_pct,
                (unsigned)mon.free_size, (unsigned)mon.free_biggest_size,
                (unsigned)mon.frag_pct);

  Serial.printf("[HEAP]  %-18s free: %u B  biggest: %u B\n", tag,
                (unsigned)heap_caps_get_free_size(MALLOC_CAP_8BIT),
                (unsigned)heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
  Serial.flush();
}