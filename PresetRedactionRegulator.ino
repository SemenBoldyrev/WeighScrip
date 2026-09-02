// Half frontend, half backend

// ВАЖНО: только функции, не переменные.
// Глобальный инициализатор выполняется ДО setup(), то есть до create_screens(),
// и запомнил бы нули - навсегда.
static lv_obj_t* name_redaction_container()       { return objects.textbox_id_3; }
static lv_obj_t* max_weight_redaction_container() { return objects.textbox_id_4; }
static lv_obj_t* min_weight_redaction_container() { return objects.textbox_id_5; }

static lv_obj_t* addition_button()                { return objects.preset_addition_button; }
static lv_obj_t* removal_button()                 { return objects.preset_removal_button; }

static paramPresetStruct presetsContainerIdsArr[MAX_PRESET_AMOUNT];

static int last_selected_section = -1;   // -1 = ничего не выбрано

static lv_obj_t* preset_slot_cont(int i) {
  switch (i) {
    case 0:  return objects.preset_select_0;
    case 1:  return objects.preset_select_1;
    case 2:  return objects.preset_select_2;
    case 3:  return objects.preset_select_3;
    case 4:  return objects.preset_select_4;
    case 5:  return objects.preset_select_5;
    case 6:  return objects.preset_select_6;
    case 7:  return objects.preset_select_7;
    case 8:  return objects.preset_select_8;
    case 9:  return objects.preset_select_9;
    default: return NULL;
  }
}

static lv_obj_t* preset_slot_label(int i) {
  switch (i) {
    case 0:  return objects.preset_name_0;
    case 1:  return objects.preset_name_1;
    case 2:  return objects.preset_name_2;
    case 3:  return objects.preset_name_3;
    case 4:  return objects.preset_name_4;
    case 5:  return objects.preset_name_5;
    case 6:  return objects.preset_name_6;
    case 7:  return objects.preset_name_7;
    case 8:  return objects.preset_name_8;
    case 9:  return objects.preset_name_9;
    default: return NULL;
  }
}
//get_var_cur_preset_amount

void add_new_section() {
  int cur_section_amount = get_var_cur_preset_amount();

  if (cur_section_amount >= MAX_PRESET_AMOUNT) return;

  // было cur_section_amount++ - постинкремент передаёт СТАРОЕ значение,
  // счётчик пресетов не рос
  set_var_cur_preset_amount(cur_section_amount + 1);
  int cur_index = cur_section_amount;
  show_preset_container(cur_index, true);

  paramPresetStruct *cur_preset = get_var_preset(cur_index);
  cur_preset -> index = cur_index;
  cur_preset -> name = "New Preset";
  cur_preset -> min = 0;
  cur_preset -> max = 0;

  set_section_name(cur_index, cur_preset -> name);

  block_removal_button(false);
  if (get_var_cur_preset_amount() >= MAX_PRESET_AMOUNT) {
    block_addition_button(true);
  }
}

void remove_section() {
  int cur_section_amount = get_var_cur_preset_amount();

  if (cur_section_amount <= 0) return;
  if (last_selected_section < 0) return;
  // было cur_section_amount-- (постдекремент, уходило старое значение)
  set_var_cur_preset_amount(cur_section_amount - 1);
  int cur_index = cur_section_amount - 1;
  show_preset_container(cur_index, false);   // было true - строку надо СКРЫТЬ

  block_addition_button(false);
  if (get_var_cur_preset_amount() <= 0) {
    block_removal_button(true);
  }

  // last_selected_section - это int, сравнение с NULL здесь бессмысленно
  
  removal_rearange_sections(last_selected_section);
  save_presets_from_section_to_sd();
  last_selected_section = -1;   // выбранного пресета больше нет
  block_redaction_section(true);
  
}


// Закрывает "дыру" после удаления пресета номер keyId: каждый следующий
// сдвигается на одну позицию вверх.
// Вызывать ПОСЛЕ уменьшения счётчика - тогда get_var_cur_preset_amount()
// уже равен новому количеству и i + 1 не вылезет за границу массива.
void removal_rearange_sections(int keyId) {
  int newAmount = get_var_cur_preset_amount();

  if (keyId < 0 || keyId > newAmount) return;

  for (int i = keyId; i < newAmount; i++) {
    paramPresetStruct *dst = get_var_preset(i);
    paramPresetStruct *src = get_var_preset(i + 1);

    dst -> name  = src -> name;
    dst -> min   = src -> min;
    dst -> max   = src -> max;
    dst -> index = i;            // номер должен совпадать с позицией
  }

  // освободившийся хвост чистим, чтобы не всплыл при следующем добавлении
  paramPresetStruct *tail = get_var_preset(newAmount);
  tail -> index = -1;
  tail -> name  = "";
  tail -> min   = 0;
  tail -> max   = 0;

  fetch_sections();   // данные сдвинулись - подписи надо перерисовать
}


// Печатает вес без хвостовых нулей:
//   5.5      -> "5.5"      (а не "5.500000")
//   0.00001  -> "0.00001"  (а не "0.000010")
//   12       -> "12"       (а не "12.000000")
// Предел точности всё равно задаёт WEIGHT_DECIMALS - что сверх него,
// то округлится ещё в snprintf.
static void format_weight(double value, char* buf, size_t size) {
  snprintf(buf, size, "%.*f", WEIGHT_DECIMALS, value);

  if (strchr(buf, '.') == NULL) return;   // целое - резать нечего

  int i = (int)strlen(buf) - 1;
  while (i > 0 && buf[i] == '0') { buf[i] = '\0'; i--; }
  if (i > 0 && buf[i] == '.') buf[i] = '\0';   // остался "5." -> "5"
}


void start_section_redaction(int id) {
  block_redaction_section(false);

  paramPresetStruct *cur_preset = get_var_preset(id);
  last_selected_section = id;

  if (name_redaction_container() == NULL) return;

  char buf[25];
  lv_textarea_set_text(name_redaction_container(), cur_preset -> name.c_str());

  format_weight(cur_preset -> max, buf, sizeof(buf));
  lv_textarea_set_text(max_weight_redaction_container(), buf);

  format_weight(cur_preset -> min, buf, sizeof(buf));
  lv_textarea_set_text(min_weight_redaction_container(), buf);
}

void fetch_sections() {
  int cur_section_amount = get_var_cur_preset_amount();

  if (cur_section_amount <= 0){
    block_addition_button(false);
    block_removal_button(true);
    return;
  }

  for (int i = 0; i < cur_section_amount; i++) {
    paramPresetStruct *cur_preset = get_var_preset(i);
    set_section_name(i, cur_preset -> name);
    show_preset_container(i, true);
  }

  block_removal_button(false);

  if (cur_section_amount >= MAX_PRESET_AMOUNT) {
    block_addition_button(true);
  }
  else {
    block_addition_button(false);
  }
}


void block_addition_button(bool block) {
  if (addition_button() == NULL) return;

  if (block) {
    lv_obj_add_state(addition_button(), LV_STATE_DISABLED);
  }
  else {
    lv_obj_clear_state(addition_button(), LV_STATE_DISABLED);
  }
}

void block_removal_button(bool block) {
  if (removal_button() == NULL) return;

  if (block) {
    lv_obj_add_state(removal_button(), LV_STATE_DISABLED);
  }
  else {
    lv_obj_clear_state(removal_button(), LV_STATE_DISABLED);
  }
}

void block_redaction_section(bool block) {
  if (name_redaction_container() == NULL || max_weight_redaction_container() == NULL || min_weight_redaction_container() == NULL) return;

  if (block) {
    lv_obj_add_state(name_redaction_container(), LV_STATE_DISABLED);
    lv_obj_add_state(max_weight_redaction_container(), LV_STATE_DISABLED);
    lv_obj_add_state(min_weight_redaction_container(), LV_STATE_DISABLED);
  }
  else {
    lv_obj_clear_state(name_redaction_container(), LV_STATE_DISABLED);
    lv_obj_clear_state(max_weight_redaction_container(), LV_STATE_DISABLED);
    lv_obj_clear_state(min_weight_redaction_container(), LV_STATE_DISABLED);
  }
}


void show_preset_container(int id, bool show) {
  lv_obj_t* cur_obj = preset_slot_cont(id);

  if (cur_obj == NULL) return;

  if (show) {
    lv_obj_clear_flag(cur_obj, LV_OBJ_FLAG_HIDDEN);
  }
  else {
    lv_obj_add_flag(cur_obj, LV_OBJ_FLAG_HIDDEN);
  }
  
}

void set_section_name(int id, String name) {
  lv_obj_t* label = preset_slot_label(id);

  if (label == NULL) return;

  lv_label_set_text(label, name.c_str());
}


void save_presets_from_sections() {
  if (last_selected_section < 0) return;

  if (name_redaction_container() == NULL ||
      max_weight_redaction_container() == NULL ||
      min_weight_redaction_container() == NULL)
      {
        show_error_message("Cannot save preset: the data is not presented");
        return;
      }

  paramPresetStruct *cur_preset = get_var_preset(last_selected_section);

  cur_preset -> name = lv_textarea_get_text(name_redaction_container());

  // strtod (не strtof) - поле теперь double, иначе точность терялась бы
  // прямо на разборе строки. Второй аргумент - указатель на конец разбора,
  // он нам не нужен.
  cur_preset -> max = strtod(lv_textarea_get_text(max_weight_redaction_container()), NULL);
  cur_preset -> min = strtod(lv_textarea_get_text(min_weight_redaction_container()), NULL);

  // Serial.println(cur_preset -> max);
  // Serial.println(cur_preset -> min);

  if (cur_preset -> max <= cur_preset -> min)
  {
    show_error_message("Cannot save preset: min value is greater / equal to the max value");
    return;
  }

  //
  save_presets_from_section_to_sd();
  //

  fetch_sections();

  Serial.println("Saved successfully!");
}

void save_presets_from_section_to_sd() {
  save_presets_to_SD(get_var_preset_arr(), get_var_cur_preset_amount());
}

