#define SD_SHOWER_AMOUNT 4

static lv_obj_t* sd_status_shower(int i) {
  switch (i) {
    case 0:  return objects.obj0__sd_status_shower;
    case 1:  return objects.obj3__sd_status_shower;
    case 2:  return objects.obj6__sd_status_shower;
    case 3:  return objects.obj8__sd_status_shower;
    default: return NULL;
  }
}


void show_sd_ok(bool isOk) {
  change_every_sd_shower_color(isOk);   // было: true в ОБЕИХ ветках
}


void change_every_sd_shower_color(bool ok) {
  uint32_t color = ok ? OK_COLOR : NOT_OK_COLOR;

  for (int i = 0; i < SD_SHOWER_AMOUNT; i++) {
    lv_obj_t* obj = sd_status_shower(i);
    if (obj == NULL) continue;

    lv_obj_set_style_bg_color(obj, lv_color_hex(color), LV_PART_MAIN);
  }
}
