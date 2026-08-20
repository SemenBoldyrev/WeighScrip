//
// GLOBALS
//
// MAX_PRESET_AMOUNT / MAX_WIFI_AMOUNT / MAX_INPUT_SIZE переехали в structures.h,
// иначе их не видят .ino-файлы, стоящие в алфавите раньше этого.

bool hand_mode;

int cur_preset_amount = 0;
int cur_wifi_amount = 0;

char date_str[15] = "01.01.0001";
char time_str[15] = "01:01";

char input_str[MAX_INPUT_SIZE] = "";

paramPresetStruct presets_arr[MAX_PRESET_AMOUNT];

paramPresetStruct *get_var_preset_arr() {
    return presets_arr;
}

paramPresetStruct *get_var_preset(int id) {
    return &presets_arr[id];
}

void set_var_presets_arr(paramPresetStruct *value) {
    // depends on current preset amount
    int presets_amount = get_var_cur_preset_amount();
    for (int i = 0; i < presets_amount; i++)
    {
      presets_arr[i].index = value -> index;
      presets_arr[i].name = value -> name;
      presets_arr[i].min = value -> min;
      presets_arr[i].max = value -> max;
    }
}


const char *get_var_input_str() {
    return input_str;
}

void set_var_input_str(const char *value) {
    strncpy(input_str, value, sizeof(input_str) / sizeof(char));
    input_str[sizeof(input_str) / sizeof(char) - 1] = 0;
}

const char *get_var_time_str() {
    return time_str;
}

void set_var_time_str(const char *value) {
    strncpy(time_str, value, sizeof(time_str) / sizeof(char));
    time_str[sizeof(time_str) / sizeof(char) - 1] = 0;
}


const char *get_var_date_str() {
    return date_str;
}

void set_var_date_str(const char *value) {
    strncpy(date_str, value, sizeof(date_str) / sizeof(char));
    date_str[sizeof(date_str) / sizeof(char) - 1] = 0;
}


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

