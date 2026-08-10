#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Style: AButtonGreen
lv_style_t *get_style_abutton_green_MAIN_DEFAULT();
lv_style_t *get_style_abutton_green_MAIN_PRESSED();
lv_style_t *get_style_abutton_green_MAIN_DISABLED();
void add_style_abutton_green(lv_obj_t *obj);
void remove_style_abutton_green(lv_obj_t *obj);

// Style: ALabelWhite
lv_style_t *get_style_alabel_white_MAIN_DEFAULT();
void add_style_alabel_white(lv_obj_t *obj);
void remove_style_alabel_white(lv_obj_t *obj);

// Style: APanelBlack
lv_style_t *get_style_apanel_black_MAIN_DEFAULT();
void add_style_apanel_black(lv_obj_t *obj);
void remove_style_apanel_black(lv_obj_t *obj);

// Style: APanelGray
lv_style_t *get_style_apanel_gray_MAIN_DEFAULT();
void add_style_apanel_gray(lv_obj_t *obj);
void remove_style_apanel_gray(lv_obj_t *obj);

// Style: ASwitch
lv_style_t *get_style_aswitch_KNOB_DEFAULT();
lv_style_t *get_style_aswitch_KNOB_CHECKED();
lv_style_t *get_style_aswitch_KNOB_DISABLED();
lv_style_t *get_style_aswitch_INDICATOR_CHECKED();
lv_style_t *get_style_aswitch_INDICATOR_DEFAULT();
lv_style_t *get_style_aswitch_INDICATOR_DISABLED();
void add_style_aswitch(lv_obj_t *obj);
void remove_style_aswitch(lv_obj_t *obj);

// Style: AButtonGray
lv_style_t *get_style_abutton_gray_MAIN_DEFAULT();
lv_style_t *get_style_abutton_gray_MAIN_PRESSED();
lv_style_t *get_style_abutton_gray_MAIN_DISABLED();
void add_style_abutton_gray(lv_obj_t *obj);
void remove_style_abutton_gray(lv_obj_t *obj);

// Style: AButtonGrayDark
lv_style_t *get_style_abutton_gray_dark_MAIN_DEFAULT();
lv_style_t *get_style_abutton_gray_dark_MAIN_PRESSED();
lv_style_t *get_style_abutton_gray_dark_MAIN_DISABLED();
void add_style_abutton_gray_dark(lv_obj_t *obj);
void remove_style_abutton_gray_dark(lv_obj_t *obj);

// Style: AButtonRed
lv_style_t *get_style_abutton_red_MAIN_DEFAULT();
lv_style_t *get_style_abutton_red_MAIN_PRESSED();
lv_style_t *get_style_abutton_red_MAIN_DISABLED();
void add_style_abutton_red(lv_obj_t *obj);
void remove_style_abutton_red(lv_obj_t *obj);

// Style: AContainerBlack
lv_style_t *get_style_acontainer_black_MAIN_DEFAULT();
void add_style_acontainer_black(lv_obj_t *obj);
void remove_style_acontainer_black(lv_obj_t *obj);

// Style: ADropdownGreen
lv_style_t *get_style_adropdown_green_MAIN_DEFAULT();
lv_style_t *get_style_adropdown_green_MAIN_PRESSED();
lv_style_t *get_style_adropdown_green_MAIN_DISABLED();
lv_style_t *get_style_adropdown_green_SELECTED_DEFAULT();
lv_style_t *get_style_adropdown_green_SELECTED_PRESSED();
lv_style_t *get_style_adropdown_green_SELECTED_DISABLED();
lv_style_t *get_style_adropdown_green_INDICATOR_DEFAULT();
lv_style_t *get_style_adropdown_green_INDICATOR_PRESSED();
lv_style_t *get_style_adropdown_green_INDICATOR_DISABLED();
void add_style_adropdown_green(lv_obj_t *obj);
void remove_style_adropdown_green(lv_obj_t *obj);

// Style: APanelRedCont
lv_style_t *get_style_apanel_red_cont_MAIN_DEFAULT();
void add_style_apanel_red_cont(lv_obj_t *obj);
void remove_style_apanel_red_cont(lv_obj_t *obj);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/