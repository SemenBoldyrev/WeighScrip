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
    SCREEN_ID_LOGS_SCREEN = 5,
    SCREEN_ID_KEYBOARD_SCREEN = 6,
    _SCREEN_ID_LAST = 6
};

typedef struct _objects_t {
    lv_obj_t *main_screen;
    lv_obj_t *hand_mode_screen;
    lv_obj_t *auto_mode_screen;
    lv_obj_t *options_screen;
    lv_obj_t *logs_screen;
    lv_obj_t *keyboard_screen;
    lv_obj_t *obj0;
    lv_obj_t *obj0__obj0;
    lv_obj_t *obj0__obj1;
    lv_obj_t *obj0__obj1__obj0;
    lv_obj_t *obj0__obj1__obj1;
    lv_obj_t *obj0__obj2;
    lv_obj_t *obj1;
    lv_obj_t *obj1__hand_mode_switch;
    lv_obj_t *textbox_id_1;
    lv_obj_t *textbox_id_2;
    lv_obj_t *obj2;
    lv_obj_t *obj2__obj0;
    lv_obj_t *obj2__obj1;
    lv_obj_t *obj2__obj1__obj0;
    lv_obj_t *obj2__obj1__obj1;
    lv_obj_t *obj2__obj2;
    lv_obj_t *obj3;
    lv_obj_t *obj3__hand_mode_switch;
    lv_obj_t *obj4;
    lv_obj_t *obj4__obj0;
    lv_obj_t *obj4__obj1;
    lv_obj_t *obj4__obj1__obj0;
    lv_obj_t *obj4__obj1__obj1;
    lv_obj_t *obj4__obj2;
    lv_obj_t *obj5;
    lv_obj_t *obj5__obj0;
    lv_obj_t *obj5__obj1;
    lv_obj_t *obj5__obj1__obj0;
    lv_obj_t *obj5__obj1__obj1;
    lv_obj_t *obj5__obj2;
    lv_obj_t *obj6;
    lv_obj_t *obj7;
    lv_obj_t *preset_option_screen;
    lv_obj_t *preset_redactor;
    lv_obj_t *obj8;
    lv_obj_t *wifi_option_screen;
    lv_obj_t *obj9;
    lv_obj_t *obj9__obj0;
    lv_obj_t *obj9__obj1;
    lv_obj_t *obj9__obj1__obj0;
    lv_obj_t *obj9__obj1__obj1;
    lv_obj_t *obj9__obj2;
    lv_obj_t *number_keyboard;
    lv_obj_t *number_keyboard__obj9;
    lv_obj_t *number_keyboard__keyboard_text_area_1;
    lv_obj_t *number_keyboard__obj10;
    lv_obj_t *text_keyboard;
    lv_obj_t *text_keyboard__obj7;
    lv_obj_t *text_keyboard__keyboard_text_area;
    lv_obj_t *text_keyboard__obj8;
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

void create_screen_logs_screen();
void tick_screen_logs_screen();

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

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/