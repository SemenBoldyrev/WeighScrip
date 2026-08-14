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

void action_request_input_change(lv_event_t *e) {
    request_input_change(get_event_user_data_int(e));
}

void action_end_input_session(lv_event_t *e) {
  end_input_session();
}
