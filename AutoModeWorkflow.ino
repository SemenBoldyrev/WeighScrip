//
//  SCRIPT FOR AUTO MOD WORKFLOW HERE
//
#define MINI_LOG_AMOUNT 5
#define MINI_LOG_TEXT_LEN 48

lv_obj_t* get_mini_log(int id) {
  switch (id)
  {
    case 0:  return objects.mini_log_1;
    case 1:  return objects.mini_log_2;
    case 2:  return objects.mini_log_3;
    case 3:  return objects.mini_log_4;
    case 4:  return objects.mini_log_5;
    default: return NULL;
  }
}

void prepeare_auto_mod()
{
  for (int i = 0; i < MINI_LOG_AMOUNT; i++) {
    lv_obj_t* label = get_mini_log(i);
    if (label == NULL) continue;
    lv_label_set_text(label, "");
  }
}



void show_check_save_auto_weight(double weight)
{
  show_next_in_mini_log(weight);
  save_auto_weight_local(weight);
  save_auto_weight_net(weight);
  check_auto_weight(weight);
}



// Пишем в буфер ВЫЗЫВАЮЩЕГО. Вернуть указатель на локальный массив нельзя -
// он умрёт вместе с функцией, а static-буфер сломается при двух вызовах
// в одном выражении.
void mini_log_format_message(double weight, char* out, size_t size)
{
  char weightBuf[26];
  format_weight(weight, weightBuf, sizeof(weightBuf));

  snprintf(out, size, "%s -> %s", get_var_time_str(), weightBuf);
}


void show_next_in_mini_log(double weight)
{
  char buf[MINI_LOG_TEXT_LEN];

  // Сдвигаем СНИЗУ ВВЕРХ: каждая строка берёт текст предыдущей.
  // Если идти сверху вниз, первая же запись затрёт источник для второй,
  // и весь список заполнится одним значением.
  for (int i = MINI_LOG_AMOUNT - 1; i > 0; i--) {
    lv_obj_t* dst = get_mini_log(i);
    lv_obj_t* src = get_mini_log(i - 1);
    if (dst == NULL || src == NULL) continue;

    const char* text = lv_label_get_text(src);
    if (text != NULL) {
      strncpy(buf, text, sizeof(buf) - 1);
      buf[sizeof(buf) - 1] = '\0';
    }
    else {
      buf[0] = '\0';
    }

    lv_label_set_text(dst, buf);
  }

  lv_obj_t* first = get_mini_log(0);
  if (first == NULL) return;

  mini_log_format_message(weight, buf, sizeof(buf));
  lv_label_set_text(first, buf);
}



// Имя текущей дозы. selected_dose == -1 означает ручной ввод пределов.
static const char* current_dose_name()
{
  int32_t id = get_var_selected_dose();

  if (id < 0 || id >= get_var_cur_preset_amount()) return "custom";

  paramPresetStruct* preset = get_var_preset(id);
  if (preset == NULL) return "custom";

  return preset -> name.c_str();
}


void check_auto_weight(double weight)
{
  double minW = get_var_min_weight();
  double maxW = get_var_max_weight();

  if (minW <= 0 && maxW <= 0) return; // minW <= 0 || minW < 0 ???

  if (weight >= minW && weight <= maxW) return;

  char weightBuf[24], minBuf[24], maxBuf[24];
  format_weight(weight, weightBuf, sizeof(weightBuf));
  format_weight(minW,   minBuf,    sizeof(minBuf));
  format_weight(maxW,   maxBuf,    sizeof(maxBuf));

  char msg[96];
  snprintf(msg, sizeof(msg), "%s out of range: %s (%s..%s)",
           weight < minW ? "underweight" : "overweight",
           weightBuf, minBuf, maxBuf);

  show_error_message(msg, false, EM_DANGER);

  // stop_auto_mod(true);
}


void save_auto_weight_local(double weight)
{
  char stamp[24];
  build_log_timestamp(stamp, sizeof(stamp));

  save_in_save_log(stamp, weight, current_dose_name(),
                   get_var_min_weight(), get_var_max_weight());
}

void save_auto_weight_net(double weight)
{
  // nothing here fow now...
}

void stop_auto_mod(bool crt = false)
{
  
}