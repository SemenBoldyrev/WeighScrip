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

double min_weight = 0.0;
double max_weight = 1.0;
char min_weight_str[17] = "0.0"; // for showing
char max_weight_str[17] = "1.0"; // for showing

bool error_message_set_ok = false;
bool error_message_set_yn = false;
char error_message_text[100] = "No error message set...";

const char *get_var_error_message_text() {
    return error_message_text;
}

void set_var_error_message_text(const char *value) {
    strncpy(error_message_text, value, sizeof(error_message_text) / sizeof(char));
    error_message_text[sizeof(error_message_text) / sizeof(char) - 1] = 0;
}

bool get_var_error_message_set_yn() {
    return error_message_set_yn;
}

void set_var_error_message_set_yn(bool value) {
    error_message_set_yn = value;
}


bool get_var_error_message_set_ok() {
    return error_message_set_ok;
}

void set_var_error_message_set_ok(bool value) {
    error_message_set_ok = value;
}


const char *get_var_max_weight_str() {
    return max_weight_str;
}

// setter is based on double setter
void set_var_max_weight_str(const char *value) {
    // strncpy(max_weight_str, value, sizeof(max_weight_str) / sizeof(char));
    // max_weight_str[sizeof(max_weight_str) / sizeof(char) - 1] = 0;
    char *end;
    set_var_max_weight(strtod(value, &end));
}


const char *get_var_min_weight_str() {
    return min_weight_str;
}

// setter is based on double setter
void set_var_min_weight_str(const char *value) {
    // strncpy(min_weight_str, value, sizeof(min_weight_str) / sizeof(char));
    // min_weight_str[sizeof(min_weight_str) / sizeof(char) - 1] = 0;
    char *end;
}


double get_var_max_weight() {
    return max_weight;
}

void set_var_max_weight(double value) {
    max_weight = value;
    // !!!FROM OUTER FUNCTION PRESETREDATIONREGULATOR!!!
    format_weight(value, max_weight_str, sizeof(max_weight_str));
    // sprintf(max_weight_str, "%f", max_weight);
}


double get_var_min_weight() {
    return min_weight;
}

void set_var_min_weight(double value) {
    min_weight = value;
    // !!!FROM OUTER FUNCTION PRESETREDATIONREGULATOR!!!
    format_weight(value, min_weight_str, sizeof(min_weight_str));
    // sprintf(min_weight_str, "%f", min_weight);
}



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
      lv_obj_add_state(objects.obj4__hand_mode_switch, LV_STATE_CHECKED);
    } 
    else 
    {
      lv_obj_remove_state(objects.obj1__hand_mode_switch, LV_STATE_CHECKED);
      lv_obj_remove_state(objects.obj4__hand_mode_switch, LV_STATE_CHECKED);
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

