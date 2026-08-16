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

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/