#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_change_screen(lv_event_t * e);
extern void action_change_screen_main(lv_event_t * e);
extern void action_test_signal(lv_event_t * e);
extern void action_change_option_screen(lv_event_t * e);
extern void action_request_input_change(lv_event_t * e);
extern void action_end_input_session(lv_event_t * e);
extern void action_update_wifi_list(lv_event_t * e);
extern void action_sync_time(lv_event_t * e);
extern void action_request_input_change_wifi(lv_event_t * e);
extern void action_add_preset_section(lv_event_t * e);
extern void action_remove_preset_section(lv_event_t * e);
extern void action_request_preset_section_redact(lv_event_t * e);
extern void action_save_presets_from_options(lv_event_t * e);
extern void action_dose_select(lv_event_t * e);
extern void action_select_dose_for_auto(lv_event_t * e);
extern void action_try_reconnect_to_wi_fi(lv_event_t * e);
extern void action_error_message_pressed_yes(lv_event_t * e);
extern void action_error_message_pressed_no(lv_event_t * e);
extern void action_set_custom_time(lv_event_t * e);
extern void action_custom_time_changed(lv_event_t * e);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/