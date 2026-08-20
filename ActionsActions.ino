//
// SIGNALS
//

int get_event_user_data_int(lv_event_t *e) {
  void * user_data_ptr = lv_event_get_user_data(e);
  return (int)(intptr_t)user_data_ptr;
}

void action_change_screen(lv_event_t *e) {
  change_screen((ScreensEnum)get_event_user_data_int(e));
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
    refresh_wifis_list();
}

void action_sync_time(lv_event_t *e) {
    sync_time(TIMEZONE_CODE);
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