#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations

// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_DATE_STR = 0,
    FLOW_GLOBAL_VARIABLE_TIME_STR = 1,
    FLOW_GLOBAL_VARIABLE_INPUT_STR = 2,
    FLOW_GLOBAL_VARIABLE_MIN_WEIGHT = 3,
    FLOW_GLOBAL_VARIABLE_MAX_WEIGHT = 4,
    FLOW_GLOBAL_VARIABLE_MIN_WEIGHT_STR = 5,
    FLOW_GLOBAL_VARIABLE_MAX_WEIGHT_STR = 6,
    FLOW_GLOBAL_VARIABLE_ERROR_MESSAGE_SET_OK = 7,
    FLOW_GLOBAL_VARIABLE_ERROR_MESSAGE_SET_YN = 8,
    FLOW_GLOBAL_VARIABLE_ERROR_MESSAGE_TEXT = 9
};

// Native global variables

extern bool get_var_hand_mode();
extern void set_var_hand_mode(bool value);
extern const char *get_var_date_str();
extern void set_var_date_str(const char *value);
extern const char *get_var_time_str();
extern void set_var_time_str(const char *value);
extern const char *get_var_input_str();
extern void set_var_input_str(const char *value);
extern double get_var_min_weight();
extern void set_var_min_weight(double value);
extern double get_var_max_weight();
extern void set_var_max_weight(double value);
extern const char *get_var_min_weight_str();
extern void set_var_min_weight_str(const char *value);
extern const char *get_var_max_weight_str();
extern void set_var_max_weight_str(const char *value);
extern bool get_var_error_message_set_ok();
extern void set_var_error_message_set_ok(bool value);
extern bool get_var_error_message_set_yn();
extern void set_var_error_message_set_yn(bool value);
extern const char *get_var_error_message_text();
extern void set_var_error_message_text(const char *value);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/