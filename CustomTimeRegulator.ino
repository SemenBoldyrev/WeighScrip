// not the best wat, but will do

#define MONTH_31 "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31"
#define MONTH_30 "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30"
#define MONTH_29 "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29"
#define MONTH_28 "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28"

static lv_obj_t* get_day_custom_dropdown() { return objects.day_custom_dropdown; }
static lv_obj_t* get_month_custom_dropdown() { return objects.month_custom_dropdown; }
static lv_obj_t* get_year_custom_dropdown() { return objects.year_custom_dropdown; }
static lv_obj_t* get_hours_custom_textbox() { return objects.textbox_id_6; }
static lv_obj_t* get_minutes_custom_textbox() { return objects.textbox_id_7; }

int str_to_int(const char *str) {
  if (str == NULL) {
    show_error_message("Values for time convertion are not presented");  
    return -1;
  }

  char *endptr;
  errno = 0;

  long val = strtol(str, &endptr, 10);

  if (endptr == str) {
    show_error_message("Error on covertig values");  
    return -1;
  }

  return (int)val;
}

bool is_leap_year(int year) {
    if (year % 4 != 0) {
        return 0;
    }
    if (year % 100 != 0) {
        return 1;
    }
    return (year % 400 == 0);
}

// bro, what is that, thanks, i think
// Сколько дней в месяце. Одно место вместо трёх разных проверок.
int days_in_month(int month, int year) {
  switch (month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
    case 4: case 6: case 9: case 11:                          return 30;
    case 2: return is_leap_year(year) ? 29 : 28;
    default: return 0;   // некорректный месяц
  }
}

bool arr_contains_value(int arr[], int size, int c) {
  for (int i = 0; i < size; i++) {
      if (arr[i] == c) {
          return true;
      }
  }
  return false;
}

void change_custom_day_selection() {
  //lv_textarea_get_text(textarea);
  char buf[8];

  lv_dropdown_get_selected_str(get_year_custom_dropdown(), buf, sizeof(buf));
  int year = str_to_int(buf);

  lv_dropdown_get_selected_str(get_month_custom_dropdown(), buf, sizeof(buf));
  int month = str_to_int(buf);

  int long_months[7] = {1, 3, 5, 7, 8, 10, 12}; 

  Serial.println(month);

  if (month == 2)
  {
    if (is_leap_year(year)) lv_dropdown_set_options(get_day_custom_dropdown(), MONTH_29);
    else lv_dropdown_set_options(get_day_custom_dropdown(), MONTH_28);
  }
  else if (arr_contains_value(long_months, 7, month)) lv_dropdown_set_options(get_day_custom_dropdown(), MONTH_31);
  else lv_dropdown_set_options(get_day_custom_dropdown(), MONTH_30);
}

bool check_given_time(int day, int month, int year, int hours, int minutes) {

  Serial.print("[CT] checking time: ");
  Serial.print(day);
  Serial.print(".");
  Serial.print(month);
  Serial.print(".");
  Serial.print(year);
  Serial.print("  ");
  Serial.print(hours);
  Serial.print(":");
  Serial.println(minutes);

  // ПОРЯДОК ВАЖЕН: сначала год и месяц, иначе days_in_month() не с чем работать
  if (year < 1970) {show_error_message("Year value is out of range, say hi to Jesus"); return false;}
  if (month < 1 || month > 12) {show_error_message("Month value is out of range"); return false;}

  int maxDay = days_in_month(month, year);
  if (day < 1 || day > maxDay) {show_error_message("Day value is out of range"); return false;}

  if (hours < 0 || hours > 23) {show_error_message("Hour value is out of range"); return false;}
  if (minutes < 0 || minutes > 59) {show_error_message("Minute value is out of range"); return false;}

  return true;
}

void change_time_to_custom() {
  char buf[8];

  lv_dropdown_get_selected_str(get_year_custom_dropdown(), buf, sizeof(buf));
  int year = str_to_int(buf);

  lv_dropdown_get_selected_str(get_month_custom_dropdown(), buf, sizeof(buf));
  int month = str_to_int(buf);

  lv_dropdown_get_selected_str(get_day_custom_dropdown(), buf, sizeof(buf));
  int day = str_to_int(buf);

  int hours = str_to_int(lv_textarea_get_text(get_hours_custom_textbox()));

  int minutes = str_to_int(lv_textarea_get_text(get_minutes_custom_textbox()));

  Serial.print("[CT] trying to set custom time: ");
  Serial.print(day);
  Serial.print(".");
  Serial.print(month);
  Serial.print(".");
  Serial.print(year);
  Serial.print("  ");
  Serial.print(hours);
  Serial.print(":");
  Serial.println(minutes);

  if (!check_given_time(day, month, year, hours, minutes)) {
    return;
  }

  // mktime() трактует структуру как МЕСТНОЕ время по переменной TZ.
  // Если её никто не выставил (а sync_time() вызывается только при наличии
  // сети - то есть как раз не в этом сценарии), часы уедут на смещение пояса.
  setenv("TZ", TIMEZONE_CODE, 1);
  tzset();

  struct tm t = {0};          // остальные поля обнулены, а не с мусором
  t.tm_year = year - 1900;    // годы с 1900
  t.tm_mon  = month - 1;      // месяцы с января (0-11)
  t.tm_mday = day;
  t.tm_hour = hours;
  t.tm_min  = minutes;
  t.tm_sec  = 0;
  t.tm_isdst = -1;            // пусть система сама решит про летнее время

  time_t t_of_day = mktime(&t);
  if (t_of_day == (time_t)-1) {
    show_error_message("Cannot convert given date");
    return;
  }

  struct timeval now = { .tv_sec = t_of_day, .tv_usec = 0 };
  settimeofday(&now, NULL);
  common_time_procedure();

  Serial.println("[CT] time successfully changed!");
}
