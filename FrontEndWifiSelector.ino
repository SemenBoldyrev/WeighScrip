//Если захочк добавить слоты
// 1. добавить в EEZ
// 2. добавить тут
// 3. увеличить "MAX_WIFI_AMOUNT"

// Указатели берём ФУНКЦИЕЙ, а не глобальной переменной: на момент
// статической инициализации create_screens() ещё не отработал и в
// objects лежат нули.
static lv_obj_t* wifi_slot_cont(int i) {
  switch (i) {
    case 0:  return objects.wifi_select_0;
    case 1:  return objects.wifi_select_1;
    case 2:  return objects.wifi_select_2;
    case 3:  return objects.wifi_select_3;
    case 4:  return objects.wifi_select_4;
    default: return NULL;
  }
}

static lv_obj_t* wifi_slot_label(int i) {
  switch (i) {
    case 0:  return objects.wifi_name_0;
    case 1:  return objects.wifi_name_1;
    case 2:  return objects.wifi_name_2;
    case 3:  return objects.wifi_name_3;
    case 4:  return objects.wifi_name_4;
    default: return NULL;
  }
}


void refresh_wifis_list() {
  hide_all_new_wifis();
  scan_network();
  show_new_wifis();
}


void hide_all_new_wifis() {
  for (int i = 0; i < MAX_WIFI_AMOUNT; i++) {
    lv_obj_t* cont = wifi_slot_cont(i);
    if (cont == NULL) continue;
    lv_obj_add_flag(cont, LV_OBJ_FLAG_HIDDEN);
  }
}


void show_new_wifis() {
  int found = get_var_cur_wifi_amount();
  if (found > MAX_WIFI_AMOUNT) found = MAX_WIFI_AMOUNT;

  for (int i = 0; i < found; i++) {
    change_wifi_name(i, get_scaned_wifi_network_data(i) -> ssid);
    show_new_wifi(i);
  }
}


void show_new_wifi(int slot) {
  lv_obj_t* cont = wifi_slot_cont(slot);
  if (cont == NULL) return;
  lv_obj_clear_flag(cont, LV_OBJ_FLAG_HIDDEN);
}


void change_wifi_name(int slot, String name) {
  lv_obj_t* label = wifi_slot_label(slot);
  if (label == NULL) return;
  lv_label_set_text(label, name.c_str());
}

void connect_to_selected_wifi(int id) {
  connect_to_wifi(get_scaned_wifi_network_data(id) -> ssid, get_var_input_str());
}
