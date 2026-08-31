#include "time.h"

// I think it possible to create a correct synchronization with the real time,
// because, right now, if time is 19 minutes and 30 seconds, the real time will change after 30 sec, but this virtual clock time after 60 sec,
// i think its will be good to create "pre-callback", which will make the first callback after time left (like 30 sec in this scenario), and then connect real callback,
// or something like this, but for now, thats enough 

bool timeOk;
struct tm timeInfo;

void init_time() {
  // Пояс выставляем ВСЕГДА, а не только при удачной синхронизации по сети:
  // от него зависят и getLocalTime(), и mktime() при ручной установке.
  setenv("TZ", TIMEZONE_CODE, 1);
  tzset();

  init_time_callback();
  //
  common_time_procedure();
  //
  timeOk = true;
}

void init_time_callback() {
  const esp_timer_create_args_t timer_args = {
        .callback = &on_time_tick,
        .name = "time_tick"
    };
    esp_timer_handle_t minute_timer;
    esp_timer_create(&timer_args, &minute_timer);
    esp_timer_start_periodic(minute_timer, 60ULL * 1000000ULL);
}

void on_time_tick(void *arg) {
  common_time_procedure();
}

void common_time_procedure() {
  update_time_info();
  update_global_time_variables();
  //show_serial_time();
}


void update_time_info() {
  getLocalTime(&timeInfo);
}

void update_global_time_variables() {
  char cur_time_str[15];
  char cur_date_str[15];

  snprintf(cur_time_str, sizeof(cur_time_str), "%02d:%02d",
         timeInfo.tm_hour, timeInfo.tm_min);

  snprintf(cur_date_str, sizeof(cur_date_str), "%02d.%02d.%d",
         timeInfo.tm_mday, timeInfo.tm_mon + 1, timeInfo.tm_year + 1900);


  set_var_time_str(cur_time_str);
  set_var_date_str(cur_date_str);
}

//it works fine without it
// void update_virtual_clock() { // <-- works with frontend

// }

void show_serial_time() {
  Serial.print("Current time: ");
  Serial.print(get_var_date_str());
  Serial.print(" ");
  Serial.println(get_var_time_str());
}

void set_new_time() {
  // TODO: ручная установка времени, когда нет сети
}