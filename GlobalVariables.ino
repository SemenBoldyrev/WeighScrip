//
// GLOBALS
//
#define MAX_PRESET_AMOUNT 25 //<-- I will store it here, at least for now
#define MAX_WIFI_AMOUNT 10

bool hand_mode;

int cur_preset_amount = 0;
int cur_wifi_amount = 0;

bool get_var_hand_mode() {
    return hand_mode;
}

void set_var_hand_mode(bool value) {
    hand_mode = value;
    
    change_to_main_screen(); //because it firstlyi giving signal on value change and only then changes value
    //<-- stupid, but should work, its not doing it automaticaly. sending seeter signal only once btw
    if (hand_mode == true) 
    {
      lv_obj_add_state(objects.obj1__hand_mode_switch, LV_STATE_CHECKED);
      lv_obj_add_state(objects.obj3__hand_mode_switch, LV_STATE_CHECKED);
    } 
    else 
    {
      lv_obj_remove_state(objects.obj1__hand_mode_switch, LV_STATE_CHECKED);
      lv_obj_remove_state(objects.obj3__hand_mode_switch, LV_STATE_CHECKED);
    }
    //
}

// int get_var_max_preset_amount() {
//   return max_preset_amount;
// }

// void set_var_max_preset_amount(int value) {
//   max_preset_amount = value;
// }

int get_var_cur_preset_amount() {
  return cur_preset_amount;
}

void set_var_cur_preset_amount(int value) {
  cur_preset_amount = value;
}

int get_var_cur_wifi_amount() {
  return cur_wifi_amount;
}

void set_var_cur_wifi_amount(int value) {
  cur_wifi_amount = value;
}