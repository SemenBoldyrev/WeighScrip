#include "styles.h"
#include "images.h"
#include "fonts.h"

#include "ui.h"
#include "screens.h"

//
// Style: AButtonGreen
//

void init_style_abutton_green_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0x009933));
    lv_style_set_shadow_width(style, 0);
    lv_style_set_shadow_ofs_y(style, 0);
};

lv_style_t *get_style_abutton_green_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_abutton_green_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_abutton_green_MAIN_PRESSED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_darken(lv_color_hex(0x009933), 64));
    lv_style_set_shadow_width(style, 0);
    lv_style_set_shadow_ofs_y(style, 0);
};

lv_style_t *get_style_abutton_green_MAIN_PRESSED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_abutton_green_MAIN_PRESSED(style);
    }
    return style;
};

void init_style_abutton_green_MAIN_DISABLED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_lighten(lv_color_hex(0x009933), 64));
    lv_style_set_shadow_width(style, 0);
    lv_style_set_shadow_ofs_y(style, 0);
};

lv_style_t *get_style_abutton_green_MAIN_DISABLED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_abutton_green_MAIN_DISABLED(style);
    }
    return style;
};

void add_style_abutton_green(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_abutton_green_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_abutton_green_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_add_style(obj, get_style_abutton_green_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
};

void remove_style_abutton_green(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_abutton_green_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_abutton_green_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_remove_style(obj, get_style_abutton_green_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
};

//
// Style: ALabelWhite
//

void init_style_alabel_white_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xffffff));
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
};

lv_style_t *get_style_alabel_white_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_alabel_white_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_alabel_white(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_alabel_white_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_alabel_white(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_alabel_white_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: APanelBlack
//

void init_style_apanel_black_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0x000000));
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 10);
};

lv_style_t *get_style_apanel_black_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_apanel_black_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_apanel_black(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_apanel_black_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_apanel_black(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_apanel_black_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: APanelGray
//

void init_style_apanel_gray_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xcccccc));
    lv_style_set_border_opa(style, 0);
};

lv_style_t *get_style_apanel_gray_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_apanel_gray_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_apanel_gray(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_apanel_gray_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_apanel_gray(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_apanel_gray_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: ASwitch
//

void init_style_aswitch_KNOB_DEFAULT(lv_style_t *style) {
    lv_style_set_border_color(style, lv_color_hex(0xff0000));
    lv_style_set_border_width(style, 2);
    lv_style_set_bg_color(style, lv_color_hex(0x000000));
};

lv_style_t *get_style_aswitch_KNOB_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_aswitch_KNOB_DEFAULT(style);
    }
    return style;
};

void init_style_aswitch_KNOB_CHECKED(lv_style_t *style) {
    lv_style_set_border_color(style, lv_color_hex(0x009933));
    lv_style_set_bg_color(style, lv_color_hex(0x000000));
    lv_style_set_border_width(style, 2);
};

lv_style_t *get_style_aswitch_KNOB_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_aswitch_KNOB_CHECKED(style);
    }
    return style;
};

void init_style_aswitch_KNOB_DISABLED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_lighten(lv_color_hex(0x000000), 64));
    lv_style_set_border_color(style, lv_color_lighten(lv_color_hex(0xff0000), 64));
    lv_style_set_border_width(style, 2);
};

lv_style_t *get_style_aswitch_KNOB_DISABLED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_aswitch_KNOB_DISABLED(style);
    }
    return style;
};

void init_style_aswitch_INDICATOR_CHECKED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xcccccc));
    lv_style_set_border_color(style, lv_color_hex(0x000000));
    lv_style_set_border_width(style, 2);
};

lv_style_t *get_style_aswitch_INDICATOR_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_aswitch_INDICATOR_CHECKED(style);
    }
    return style;
};

void init_style_aswitch_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xcccccc));
    lv_style_set_border_color(style, lv_color_hex(0x000000));
    lv_style_set_border_width(style, 2);
};

lv_style_t *get_style_aswitch_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_aswitch_INDICATOR_DEFAULT(style);
    }
    return style;
};

void init_style_aswitch_INDICATOR_DISABLED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xcccccc));
    lv_style_set_border_color(style, lv_color_lighten(lv_color_hex(0x000000), 64));
    lv_style_set_border_width(style, 2);
};

lv_style_t *get_style_aswitch_INDICATOR_DISABLED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_aswitch_INDICATOR_DISABLED(style);
    }
    return style;
};

void add_style_aswitch(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_aswitch_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_aswitch_KNOB_CHECKED(), LV_PART_KNOB | LV_STATE_CHECKED);
    lv_obj_add_style(obj, get_style_aswitch_KNOB_DISABLED(), LV_PART_KNOB | LV_STATE_DISABLED);
    lv_obj_add_style(obj, get_style_aswitch_INDICATOR_CHECKED(), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_add_style(obj, get_style_aswitch_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_aswitch_INDICATOR_DISABLED(), LV_PART_INDICATOR | LV_STATE_DISABLED);
};

void remove_style_aswitch(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_aswitch_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_aswitch_KNOB_CHECKED(), LV_PART_KNOB | LV_STATE_CHECKED);
    lv_obj_remove_style(obj, get_style_aswitch_KNOB_DISABLED(), LV_PART_KNOB | LV_STATE_DISABLED);
    lv_obj_remove_style(obj, get_style_aswitch_INDICATOR_CHECKED(), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_remove_style(obj, get_style_aswitch_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_aswitch_INDICATOR_DISABLED(), LV_PART_INDICATOR | LV_STATE_DISABLED);
};

//
// Style: AButtonGray
//

void init_style_abutton_gray_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xcccccc));
    lv_style_set_shadow_width(style, 0);
    lv_style_set_shadow_ofs_y(style, 0);
    lv_style_set_text_color(style, lv_color_hex(0x000000));
};

lv_style_t *get_style_abutton_gray_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_abutton_gray_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_abutton_gray_MAIN_PRESSED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_darken(lv_color_hex(0xcccccc), 64));
    lv_style_set_shadow_width(style, 0);
    lv_style_set_shadow_ofs_y(style, 0);
    lv_style_set_text_color(style, lv_color_hex(0x000000));
};

lv_style_t *get_style_abutton_gray_MAIN_PRESSED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_abutton_gray_MAIN_PRESSED(style);
    }
    return style;
};

void init_style_abutton_gray_MAIN_DISABLED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_lighten(lv_color_hex(0xcccccc), 64));
    lv_style_set_shadow_width(style, 0);
    lv_style_set_shadow_ofs_y(style, 0);
    lv_style_set_text_color(style, lv_color_lighten(lv_color_hex(0x000000), 64));
};

lv_style_t *get_style_abutton_gray_MAIN_DISABLED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_abutton_gray_MAIN_DISABLED(style);
    }
    return style;
};

void add_style_abutton_gray(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_abutton_gray_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_abutton_gray_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_add_style(obj, get_style_abutton_gray_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
};

void remove_style_abutton_gray(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_abutton_gray_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_abutton_gray_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_remove_style(obj, get_style_abutton_gray_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
};

//
// Style: AButtonGrayDark
//

void init_style_abutton_gray_dark_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xb3b3b3));
    lv_style_set_shadow_width(style, 0);
    lv_style_set_shadow_ofs_y(style, 0);
    lv_style_set_text_color(style, lv_color_hex(0x000000));
};

lv_style_t *get_style_abutton_gray_dark_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_abutton_gray_dark_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_abutton_gray_dark_MAIN_PRESSED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_darken(lv_color_hex(0xb3b3b3), 64));
    lv_style_set_shadow_width(style, 0);
    lv_style_set_shadow_ofs_y(style, 0);
    lv_style_set_text_color(style, lv_color_hex(0x000000));
};

lv_style_t *get_style_abutton_gray_dark_MAIN_PRESSED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_abutton_gray_dark_MAIN_PRESSED(style);
    }
    return style;
};

void init_style_abutton_gray_dark_MAIN_DISABLED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_lighten(lv_color_hex(0xb3b3b3), 64));
    lv_style_set_shadow_width(style, 0);
    lv_style_set_shadow_ofs_y(style, 0);
    lv_style_set_text_color(style, lv_color_hex(0x000000));
};

lv_style_t *get_style_abutton_gray_dark_MAIN_DISABLED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_abutton_gray_dark_MAIN_DISABLED(style);
    }
    return style;
};

void add_style_abutton_gray_dark(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_abutton_gray_dark_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_abutton_gray_dark_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_add_style(obj, get_style_abutton_gray_dark_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
};

void remove_style_abutton_gray_dark(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_abutton_gray_dark_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_abutton_gray_dark_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_remove_style(obj, get_style_abutton_gray_dark_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
};

//
// Style: AButtonRed
//

void init_style_abutton_red_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff0000));
    lv_style_set_shadow_width(style, 0);
    lv_style_set_shadow_ofs_y(style, 0);
};

lv_style_t *get_style_abutton_red_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_abutton_red_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_abutton_red_MAIN_PRESSED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_darken(lv_color_hex(0xff0000), 64));
    lv_style_set_shadow_width(style, 0);
    lv_style_set_shadow_ofs_y(style, 0);
};

lv_style_t *get_style_abutton_red_MAIN_PRESSED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_abutton_red_MAIN_PRESSED(style);
    }
    return style;
};

void init_style_abutton_red_MAIN_DISABLED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_lighten(lv_color_hex(0xff0000), 64));
    lv_style_set_shadow_width(style, 0);
    lv_style_set_shadow_ofs_y(style, 0);
};

lv_style_t *get_style_abutton_red_MAIN_DISABLED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_abutton_red_MAIN_DISABLED(style);
    }
    return style;
};

void add_style_abutton_red(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_abutton_red_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_abutton_red_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_add_style(obj, get_style_abutton_red_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
};

void remove_style_abutton_red(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_abutton_red_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_abutton_red_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_remove_style(obj, get_style_abutton_red_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
};

//
// Style: AContainerBlack
//

void init_style_acontainer_black_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xffffff));
    lv_style_set_radius(style, 10);
    lv_style_set_bg_color(style, lv_color_hex(0x000000));
    lv_style_set_bg_opa(style, 255);
};

lv_style_t *get_style_acontainer_black_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_acontainer_black_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_acontainer_black(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_acontainer_black_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_acontainer_black(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_acontainer_black_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: ADropdownGreen
//

void init_style_adropdown_green_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0x009933));
    lv_style_set_text_color(style, lv_color_hex(0xffffff));
    lv_style_set_outline_color(style, lv_color_hex(0xffffff));
};

lv_style_t *get_style_adropdown_green_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_adropdown_green_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_adropdown_green_MAIN_PRESSED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_darken(lv_color_hex(0x009933), 64));
};

lv_style_t *get_style_adropdown_green_MAIN_PRESSED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_adropdown_green_MAIN_PRESSED(style);
    }
    return style;
};

void init_style_adropdown_green_MAIN_DISABLED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_lighten(lv_color_hex(0x009933), 64));
};

lv_style_t *get_style_adropdown_green_MAIN_DISABLED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_adropdown_green_MAIN_DISABLED(style);
    }
    return style;
};

void init_style_adropdown_green_SELECTED_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xffffff));
    lv_style_set_bg_color(style, lv_color_hex(0x009933));
    lv_style_set_border_color(style, lv_color_hex(0xffffff));
    lv_style_set_border_width(style, 2);
};

lv_style_t *get_style_adropdown_green_SELECTED_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_adropdown_green_SELECTED_DEFAULT(style);
    }
    return style;
};

void init_style_adropdown_green_SELECTED_PRESSED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_darken(lv_color_hex(0x009933), 64));
};

lv_style_t *get_style_adropdown_green_SELECTED_PRESSED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_adropdown_green_SELECTED_PRESSED(style);
    }
    return style;
};

void init_style_adropdown_green_SELECTED_DISABLED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_lighten(lv_color_hex(0x009933), 64));
};

lv_style_t *get_style_adropdown_green_SELECTED_DISABLED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_adropdown_green_SELECTED_DISABLED(style);
    }
    return style;
};

void init_style_adropdown_green_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0x009933));
    lv_style_set_border_color(style, lv_color_hex(0xffffff));
    lv_style_set_border_width(style, 2);
    lv_style_set_text_color(style, lv_color_hex(0xffffff));
};

lv_style_t *get_style_adropdown_green_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_adropdown_green_INDICATOR_DEFAULT(style);
    }
    return style;
};

void init_style_adropdown_green_INDICATOR_PRESSED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_darken(lv_color_hex(0x009933), 64));
};

lv_style_t *get_style_adropdown_green_INDICATOR_PRESSED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_adropdown_green_INDICATOR_PRESSED(style);
    }
    return style;
};

void init_style_adropdown_green_INDICATOR_DISABLED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_lighten(lv_color_hex(0x009933), 64));
};

lv_style_t *get_style_adropdown_green_INDICATOR_DISABLED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_adropdown_green_INDICATOR_DISABLED(style);
    }
    return style;
};

void add_style_adropdown_green(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_adropdown_green_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_adropdown_green_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_add_style(obj, get_style_adropdown_green_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_add_style(obj, get_style_adropdown_green_SELECTED_DEFAULT(), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_adropdown_green_SELECTED_PRESSED(), LV_PART_SELECTED | LV_STATE_PRESSED);
    lv_obj_add_style(obj, get_style_adropdown_green_SELECTED_DISABLED(), LV_PART_SELECTED | LV_STATE_DISABLED);
    lv_obj_add_style(obj, get_style_adropdown_green_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_adropdown_green_INDICATOR_PRESSED(), LV_PART_INDICATOR | LV_STATE_PRESSED);
    lv_obj_add_style(obj, get_style_adropdown_green_INDICATOR_DISABLED(), LV_PART_INDICATOR | LV_STATE_DISABLED);
};

void remove_style_adropdown_green(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_adropdown_green_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_adropdown_green_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_remove_style(obj, get_style_adropdown_green_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_remove_style(obj, get_style_adropdown_green_SELECTED_DEFAULT(), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_adropdown_green_SELECTED_PRESSED(), LV_PART_SELECTED | LV_STATE_PRESSED);
    lv_obj_remove_style(obj, get_style_adropdown_green_SELECTED_DISABLED(), LV_PART_SELECTED | LV_STATE_DISABLED);
    lv_obj_remove_style(obj, get_style_adropdown_green_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_adropdown_green_INDICATOR_PRESSED(), LV_PART_INDICATOR | LV_STATE_PRESSED);
    lv_obj_remove_style(obj, get_style_adropdown_green_INDICATOR_DISABLED(), LV_PART_INDICATOR | LV_STATE_DISABLED);
};

//
// Style: APanelRedCont
//

void init_style_apanel_red_cont_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_opa(style, 0);
    lv_style_set_border_color(style, lv_color_hex(0xff0000));
    lv_style_set_border_width(style, 3);
};

lv_style_t *get_style_apanel_red_cont_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_apanel_red_cont_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_apanel_red_cont(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_apanel_red_cont_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_apanel_red_cont(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_apanel_red_cont_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
//
//

void add_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*AddStyleFunc)(lv_obj_t *obj);
    static const AddStyleFunc add_style_funcs[] = {
        add_style_abutton_green,
        add_style_alabel_white,
        add_style_apanel_black,
        add_style_apanel_gray,
        add_style_aswitch,
        add_style_abutton_gray,
        add_style_abutton_gray_dark,
        add_style_abutton_red,
        add_style_acontainer_black,
        add_style_adropdown_green,
        add_style_apanel_red_cont,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_abutton_green,
        remove_style_alabel_white,
        remove_style_apanel_black,
        remove_style_apanel_gray,
        remove_style_aswitch,
        remove_style_abutton_gray,
        remove_style_abutton_gray_dark,
        remove_style_abutton_red,
        remove_style_acontainer_black,
        remove_style_adropdown_green,
        remove_style_apanel_red_cont,
    };
    remove_style_funcs[styleIndex](obj);
}