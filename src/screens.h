#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_MAIN_SCREEN = 1,
    SCREEN_ID_HAND_MODE_SCREEN = 2,
    SCREEN_ID_AUTO_MODE_SCREEN = 3,
    SCREEN_ID_OPTIONS_SCREEN = 4,
    SCREEN_ID_KEYBOARD_SCREEN = 5,
    _SCREEN_ID_LAST = 5
};

typedef struct _objects_t {
    lv_obj_t *main_screen;
    lv_obj_t *hand_mode_screen;
    lv_obj_t *auto_mode_screen;
    lv_obj_t *options_screen;
    lv_obj_t *keyboard_screen;
    lv_obj_t *obj0;
    lv_obj_t *obj0__obj0;
    lv_obj_t *obj0__obj1;
    lv_obj_t *obj0__obj1__obj0;
    lv_obj_t *obj0__obj1__obj1;
    lv_obj_t *obj0__obj2;
    lv_obj_t *obj0__wifi_status_shower;
    lv_obj_t *obj0__sd_status_shower;
    lv_obj_t *obj1;
    lv_obj_t *obj1__hand_mode_switch;
    lv_obj_t *selection_dropbox;
    lv_obj_t *textbox_id_1;
    lv_obj_t *textbox_id_2;
    lv_obj_t *obj2;
    lv_obj_t *obj2__error_message_container;
    lv_obj_t *obj2__obj12;
    lv_obj_t *obj2__error_message_panel;
    lv_obj_t *obj2__ok_error_button;
    lv_obj_t *obj2__yes_error_button;
    lv_obj_t *obj2__no_error_button;
    lv_obj_t *obj2__obj13;
    lv_obj_t *obj3;
    lv_obj_t *obj3__obj0;
    lv_obj_t *obj3__obj1;
    lv_obj_t *obj3__obj1__obj0;
    lv_obj_t *obj3__obj1__obj1;
    lv_obj_t *obj3__obj2;
    lv_obj_t *obj3__wifi_status_shower;
    lv_obj_t *obj3__sd_status_shower;
    lv_obj_t *obj4;
    lv_obj_t *obj4__hand_mode_switch;
    lv_obj_t *obj5;
    lv_obj_t *obj5__error_message_container;
    lv_obj_t *obj5__obj12;
    lv_obj_t *obj5__error_message_panel;
    lv_obj_t *obj5__ok_error_button;
    lv_obj_t *obj5__yes_error_button;
    lv_obj_t *obj5__no_error_button;
    lv_obj_t *obj5__obj13;
    lv_obj_t *obj6;
    lv_obj_t *obj6__obj0;
    lv_obj_t *obj6__obj1;
    lv_obj_t *obj6__obj1__obj0;
    lv_obj_t *obj6__obj1__obj1;
    lv_obj_t *obj6__obj2;
    lv_obj_t *obj6__wifi_status_shower;
    lv_obj_t *obj6__sd_status_shower;
    lv_obj_t *min_weight_label;
    lv_obj_t *max_weight_label;
    lv_obj_t *mini_log_1;
    lv_obj_t *mini_log_2;
    lv_obj_t *mini_log_3;
    lv_obj_t *mini_log_4;
    lv_obj_t *mini_log_5;
    lv_obj_t *obj7;
    lv_obj_t *obj7__error_message_container;
    lv_obj_t *obj7__obj12;
    lv_obj_t *obj7__error_message_panel;
    lv_obj_t *obj7__ok_error_button;
    lv_obj_t *obj7__yes_error_button;
    lv_obj_t *obj7__no_error_button;
    lv_obj_t *obj7__obj13;
    lv_obj_t *obj8;
    lv_obj_t *obj8__obj0;
    lv_obj_t *obj8__obj1;
    lv_obj_t *obj8__obj1__obj0;
    lv_obj_t *obj8__obj1__obj1;
    lv_obj_t *obj8__obj2;
    lv_obj_t *obj8__wifi_status_shower;
    lv_obj_t *obj8__sd_status_shower;
    lv_obj_t *obj9;
    lv_obj_t *obj10;
    lv_obj_t *preset_option_screen;
    lv_obj_t *textbox_id_3;
    lv_obj_t *textbox_id_4;
    lv_obj_t *textbox_id_5;
    lv_obj_t *preset_select_0;
    lv_obj_t *preset_name_0;
    lv_obj_t *preset_select_1;
    lv_obj_t *preset_name_1;
    lv_obj_t *preset_select_2;
    lv_obj_t *preset_name_2;
    lv_obj_t *preset_select_3;
    lv_obj_t *preset_name_3;
    lv_obj_t *preset_select_4;
    lv_obj_t *preset_name_4;
    lv_obj_t *preset_select_5;
    lv_obj_t *preset_name_5;
    lv_obj_t *preset_select_6;
    lv_obj_t *preset_name_6;
    lv_obj_t *preset_select_7;
    lv_obj_t *preset_name_7;
    lv_obj_t *preset_select_8;
    lv_obj_t *preset_name_8;
    lv_obj_t *preset_select_9;
    lv_obj_t *preset_name_9;
    lv_obj_t *preset_removal_button;
    lv_obj_t *preset_addition_button;
    lv_obj_t *wifi_option_screen;
    lv_obj_t *wifi_holder;
    lv_obj_t *wifi_select_0;
    lv_obj_t *wifi_name_0;
    lv_obj_t *wifi_select_1;
    lv_obj_t *wifi_name_1;
    lv_obj_t *wifi_select_2;
    lv_obj_t *wifi_name_2;
    lv_obj_t *wifi_select_3;
    lv_obj_t *wifi_name_3;
    lv_obj_t *wifi_select_4;
    lv_obj_t *wifi_name_4;
    lv_obj_t *time_option_screen;
    lv_obj_t *day_custom_dropdown;
    lv_obj_t *month_custom_dropdown;
    lv_obj_t *year_custom_dropdown;
    lv_obj_t *textbox_id_6;
    lv_obj_t *textbox_id_7;
    lv_obj_t *obj11;
    lv_obj_t *obj11__spiner_container;
    lv_obj_t *obj11__obj11;
    lv_obj_t *obj12;
    lv_obj_t *obj12__error_message_container;
    lv_obj_t *obj12__obj12;
    lv_obj_t *obj12__error_message_panel;
    lv_obj_t *obj12__ok_error_button;
    lv_obj_t *obj12__yes_error_button;
    lv_obj_t *obj12__no_error_button;
    lv_obj_t *obj12__obj13;
    lv_obj_t *number_keyboard;
    lv_obj_t *number_keyboard__obj9;
    lv_obj_t *number_keyboard__keyboard_text_area_1;
    lv_obj_t *number_keyboard__obj10;
    lv_obj_t *text_keyboard;
    lv_obj_t *text_keyboard__obj7;
    lv_obj_t *text_keyboard__keyboard_text_area;
    lv_obj_t *text_keyboard__obj8;
    lv_obj_t *obj13;
    lv_obj_t *obj13__spiner_container;
    lv_obj_t *obj13__obj11;
} objects_t;

extern objects_t objects;

void create_screen_main_screen();
void tick_screen_main_screen();

void create_screen_hand_mode_screen();
void tick_screen_hand_mode_screen();

void create_screen_auto_mode_screen();
void tick_screen_auto_mode_screen();

void create_screen_options_screen();
void tick_screen_options_screen();

void create_screen_keyboard_screen();
void tick_screen_keyboard_screen();

void create_user_widget_bottom_panel(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_bottom_panel(int startWidgetIndex);

void create_user_widget_date_time(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_date_time(int startWidgetIndex);

void create_user_widget_dose_shower(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_dose_shower(int startWidgetIndex);

void create_user_widget_logo_name(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_logo_name(int startWidgetIndex);

void create_user_widget_split_button_switch(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_split_button_switch(int startWidgetIndex);

void create_user_widget_preset_redaction_node(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_preset_redaction_node(int startWidgetIndex);

void create_user_widget_keyboard_input_widget(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_keyboard_input_widget(int startWidgetIndex);

void create_user_widget_number_input_widget(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_number_input_widget(int startWidgetIndex);

void create_user_widget_spinner_shower_widget(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_spinner_shower_widget(int startWidgetIndex);

void create_user_widget_error_message_widget(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_error_message_widget(int startWidgetIndex);

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/