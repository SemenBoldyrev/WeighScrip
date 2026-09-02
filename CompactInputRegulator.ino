const ScreensEnum keyboardScreen = SCREEN_ID_KEYBOARD_SCREEN;

static int prevScreenId = (int)SCREEN_ID_MAIN_SCREEN;
static int lastReqTextboxId = -1;

static lv_obj_t* cur_target = NULL;

static int numerical_keyboard_ids[6] = {1, 2, 4, 5, 6, 7};
static int numerical_keyboards_check_ids[4] = {1,2,4,5};
static int numerical_keyboard_ids_size = sizeof(numerical_keyboard_ids) / sizeof(numerical_keyboard_ids[0]);
static int numerical_keyboards_check_ids_size = sizeof(numerical_keyboards_check_ids) / sizeof(numerical_keyboards_check_ids[0]);

char redacted_numerical_string[MAX_INPUT_SIZE] = "";


void request_input_change(int textboxId) {
  if (get_cur_screen_id() == (int)keyboardScreen) return;

  Serial.print("Requested input change for textbox id ");
  Serial.println(textboxId);

  lastReqTextboxId = textboxId;
  prevScreenId     = get_cur_screen_id();

  set_cur_str_container_pointer(textboxId);
  if (cur_target != NULL) set_var_input_str(lv_textarea_get_text(cur_target));
  else set_var_input_str("");

  set_keyboard_visible(textboxId);
  change_screen(keyboardScreen);
}


void end_input_session() {
  //
  show_spiner(1);
  //

  if (cur_target != NULL) {
    if (numerical_keyboard_has_id(lastReqTextboxId)) lv_textarea_set_text(cur_target, redact_numerical_input_value(get_var_input_str()));
    else lv_textarea_set_text(cur_target, get_var_input_str());
  }

  if (lastReqTextboxId == 1 || lastReqTextboxId == 2) set_var_selected_dose(-1); // to see, if the preset is custom

  change_screen((ScreensEnum)prevScreenId);
  //
  hide_all_spiners();
  //

  Serial.print("Requested input change for textbox sucessful id ");
  Serial.println(lastReqTextboxId);
  Serial.print("data: ");
  Serial.println(get_var_input_str());
}


void set_cur_str_container_pointer(int id) {
  switch (id) {
    case 1:
      cur_target = objects.textbox_id_1;
      break;

    case 2:
      cur_target = objects.textbox_id_2;
      break;

    case 3:
      cur_target = objects.textbox_id_3;
      break;

    case 4:
      cur_target = objects.textbox_id_4;
      break;

    case 5:
      cur_target = objects.textbox_id_5;
      break;
    
    case 6:
      cur_target = objects.textbox_id_6;
      break;
    
    case 7:
      cur_target = objects.textbox_id_7;
      break;

    default:
      cur_target = NULL;
      Serial.printf("!! unknown textbox id %d\n", id);
      break;
  }
}


void set_keyboard_visible(int keyboardId) {
  if (objects.text_keyboard == NULL || objects.number_keyboard == NULL) {
    Serial.println("!! keyboard screen not created yet");
    return;
  }

  if (!numerical_keyboard_has_id(keyboardId))
  {
    lv_obj_clear_flag(objects.text_keyboard, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(objects.number_keyboard, LV_OBJ_FLAG_HIDDEN);
  }
  else
  {
    lv_obj_clear_flag(objects.number_keyboard, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(objects.text_keyboard, LV_OBJ_FLAG_HIDDEN);
  }
}


int get_last_req_textbox_id() {
  return lastReqTextboxId;
}


// will change later
// проверка, входит ли id в список полей с числовой клавиатурой
bool numerical_keyboard_has_id(int value) {
  for (int i = 0; i < numerical_keyboard_ids_size; i++) {
    if (numerical_keyboard_ids[i] == value) {
      return true;
    }
  }
  return false;
}

bool numerical_keyboard_check_has_id(int value) {
  for (int i = 0; i < numerical_keyboards_check_ids_size; i++) {
    if (numerical_keyboards_check_ids[i] == value) {
      return true;
    }
  }
  return false;
}


const char* redact_numerical_input_value(const char* value) {
  bool already_has_dot = false;
  int out = 0;

  // Длина строки - это strlen(), а не sizeof(): value здесь указатель,
  // и sizeof дал бы 4 (размер самого указателя) при любом вводе.
  for (int i = 0; value[i] != '\0' && out < MAX_INPUT_SIZE - 1; i++) {
    char c = value[i];   // сравниваем с '.', а не с "." - это символ, не строка

    if (c == '+' || c == '-') continue;

    if (c == '.') {
      if (already_has_dot || i == 0) continue;   // вторую и последующие выбрасываем
      already_has_dot = true;
    }

    redacted_numerical_string[out] = c;
    out++;
  }

  // "5." -> "5"
  if (out > 0 && redacted_numerical_string[out - 1] == '.') out--;

  redacted_numerical_string[out] = '\0';
  return redacted_numerical_string;
}