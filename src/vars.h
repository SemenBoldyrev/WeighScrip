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
    FLOW_GLOBAL_VARIABLE_INPUT_STR = 2
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

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/