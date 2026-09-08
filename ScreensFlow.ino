int curScreenId;

void change_to_main_screen() {
  if (get_var_hand_mode() == true) change_screen(SCREEN_ID_HAND_MODE_SCREEN);
  else change_screen(SCREEN_ID_MAIN_SCREEN);
}

void change_screen(ScreensEnum screen) {
  char msg[48];
  snprintf(msg, sizeof(msg),"Changing Screen To: %d", screen);
  show_in_console_save_in_log("screen", msg);
  loadScreen(screen);
  show_in_console_save_in_log("screen", "Screen Changed");
  curScreenId = (int)screen;
}

void change_option_sub_screen(int screen) {
  if (objects.preset_option_screen == NULL) {
    Serial.println("!! preset_option_screen == NULL, screen not created yet");
    return;
  }

  show_stack_info("before sub-screen");

  switch(screen)
  {
    case 0:
      lv_obj_add_flag(objects.preset_option_screen, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.wifi_option_screen, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.time_option_screen, LV_OBJ_FLAG_HIDDEN);

      break;

    case 1:
      change_option_sub_screen(0);
      lv_obj_clear_flag(objects.preset_option_screen, LV_OBJ_FLAG_HIDDEN);
      break;

    case 2:
      change_option_sub_screen(0);
      lv_obj_clear_flag(objects.wifi_option_screen, LV_OBJ_FLAG_HIDDEN);
      break;

      case 3:
      change_option_sub_screen(0);
      lv_obj_clear_flag(objects.time_option_screen, LV_OBJ_FLAG_HIDDEN);
      break;
  }

  show_stack_info("after sub-screen");
}

int get_cur_screen_id() {
  return curScreenId;
}