//
// SIGNALS
//

int get_event_user_data_int(lv_event_t *e) {
  void * user_data_ptr = lv_event_get_user_data(e);
  return (int)(intptr_t)user_data_ptr;
}

void action_change_screen(lv_event_t *e) {
  ScreensEnum nxtScreen = (ScreensEnum)get_event_user_data_int(e);
  // for quality control
    if (nxtScreen == SCREEN_ID_AUTO_MODE_SCREEN && get_var_min_weight() >= get_var_max_weight())
    {
        show_error_message("Cannot start auto mod: min value is greater / equal to the max value");
        return;
    }
  //
  change_screen(nxtScreen);
}

void action_change_screen_main(lv_event_t *e) {
  change_to_main_screen();
}

int test_value = 0;
void action_test_signal(lv_event_t *e) {
    Serial.print("Test ");
    Serial.print(get_event_user_data_int(e));
    Serial.print(": ");
    Serial.println(test_value);
    test_value ++;
}

void action_change_option_screen(lv_event_t *e) {
  change_option_sub_screen(get_event_user_data_int(e));
}


void action_update_wifi_list(lv_event_t *e) {
    show_spiner(0);
    refresh_wifis_list();
    hide_all_spiners();
}

void action_sync_time(lv_event_t *e) {
    show_spiner(0);
    sync_time(TIMEZONE_CODE);
    hide_all_spiners();
}


int callback_id = 0;
int callback_data = 0;

void action_request_input_change(lv_event_t *e) {
    callback_id = 0;
    callback_data = 0;
    request_input_change(get_event_user_data_int(e));
}

void action_request_input_change_wifi(lv_event_t *e) {
    callback_id = 1;
    callback_data = get_event_user_data_int(e);
    request_input_change(0);
}

void action_end_input_session(lv_event_t *e) {
    end_input_session();
    
    if (callback_id <= 0) return;
    switch (callback_id) {
      case 1: //for wifi connection try
        connect_to_selected_wifi(callback_data);
        break;
      default: break;
    }

    callback_id = 0;
    callback_data = 0;
}

void action_add_preset_section(lv_event_t *e) {
    add_new_section();
}

void action_remove_preset_section(lv_event_t *e) {
    remove_section();
}

void action_request_preset_section_redact(lv_event_t *e) {
    start_section_redaction(get_event_user_data_int(e));
}

void action_save_presets_from_options(lv_event_t *e) {
    save_presets_from_sections();
}

void action_select_dose_for_auto(lv_event_t *e) {
    select_change_dose();
}

void action_try_reconnect_to_wi_fi(lv_event_t *e) {
    show_spiner(0);
    wifi_try_reconnect();
    hide_all_spiners();
}

void action_error_message_pressed_yes(lv_event_t *e) {
    Serial.println("[EM] 'YES' or 'OK' is pressed");
    hide_error_message();   // без этого окно уже не закрыть
}

void action_error_message_pressed_no(lv_event_t *e) {
    Serial.println("[EM] 'NO' is pressed");
    hide_error_message();
}

void action_set_custom_time(lv_event_t *e) {
    change_time_to_custom();
}

void action_custom_time_changed(lv_event_t *e) {
    change_custom_day_selection();
}

