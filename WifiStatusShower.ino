#define WIFI_SHOWER_AMOUNT 4

// ВАЖНО: функция, а не массив-инициализатор.
// Глобальный массив заполнялся бы ДО create_screens(), то есть нулями.
static lv_obj_t* wifi_status_shower(int i) {
  switch (i) {
    case 0:  return objects.obj0__wifi_status_shower;
    case 1:  return objects.obj3__wifi_status_shower;
    case 2:  return objects.obj6__wifi_status_shower;
    case 3:  return objects.obj8__wifi_status_shower;
    default: return NULL;
  }
}


void show_wifi_ok(bool isOk) {
  change_every_wifi_shower_color(isOk);   // было: true в ОБЕИХ ветках
}


void change_every_wifi_shower_color(bool ok) {
  uint32_t color = ok ? OK_COLOR : NOT_OK_COLOR;

  for (int i = 0; i < WIFI_SHOWER_AMOUNT; i++) {
    lv_obj_t* obj = wifi_status_shower(i);
    if (obj == NULL) continue;

    lv_obj_set_style_bg_color(obj, lv_color_hex(color), LV_PART_MAIN);
  }
}
