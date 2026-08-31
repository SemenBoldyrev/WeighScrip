const ScreensEnum keyboardScreen = SCREEN_ID_KEYBOARD_SCREEN;

static int prevScreenId = (int)SCREEN_ID_MAIN_SCREEN;
static int lastReqTextboxId = -1;

static lv_obj_t* cur_target = NULL;

static int numerical_keyboard_ids[6] = {1, 2, 4, 5, 6, 7};
static int numerical_keyboard_ids_size = sizeof(numerical_keyboard_ids) / sizeof(numerical_keyboard_ids[0]);


void request_input_change(int textboxId) {
  if (get_cur_screen_id() == (int)keyboardScreen) return;

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
    lv_textarea_set_text(cur_target, get_var_input_str());
  }

  change_screen((ScreensEnum)prevScreenId);
  //
  hide_all_spiners();
  //
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

  if (!numerical_keyboard_id(keyboardId))
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


// проверка, входит ли id в список полей с числовой клавиатурой
bool numerical_keyboard_id(int value) {
  for (int i = 0; i < numerical_keyboard_ids_size; i++) {
    if (numerical_keyboard_ids[i] == value) {
      return true;
    }
  }
  return false;
}
