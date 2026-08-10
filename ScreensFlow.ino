void change_to_main_screen() {
  if (get_var_hand_mode() == true) change_screen(SCREEN_ID_HAND_MODE_SCREEN);
  else change_screen(SCREEN_ID_MAIN_SCREEN);
}

void change_screen(ScreensEnum screen) {
  Serial.print("Changing Screen To: ");
  Serial.println(screen);
  loadScreen(screen);
  Serial.println("Screen Changed");
}

void change_option_sub_screen(int screen) {
  switch(screen)
  {
    case 0:
      lv_obj_add_flag(objects.preset_option_screen, LV_OBJ_FLAG_HIDDEN);
      break;
    
    case 1:
      change_option_sub_screen(0);
      lv_obj_clear_flag(objects.preset_option_screen, LV_OBJ_FLAG_HIDDEN);
      break;
  }
}