#define ERROR_MESSAGE_CONT_AMOUNT 4


// ВНЕШНЯЯ обёртка на весь экран - именно на неё EEZ вешает HIDDEN при
// создании (screens.c: строки 415, 691, 1077, 2489). Внутренний
// objX__error_message_container трогать бесполезно: он ребёнок скрытого
// родителя, а скрытый родитель не рисуется вместе со всем поддеревом.
static lv_obj_t* get_em_container(int i) {
  switch (i) {
    case 0:  return objects.obj2;    // main
    case 1:  return objects.obj5;    // hand
    case 2:  return objects.obj7;    // auto
    case 3:  return objects.obj12;   // options
    default: return NULL;
  }
}

static lv_obj_t* get_em_panel(int i) {
  switch (i) {
    case 0:  return objects.obj2__error_message_panel;
    case 1:  return objects.obj5__error_message_panel;
    case 2:  return objects.obj7__error_message_panel;
    case 3:  return objects.obj12__error_message_panel;
    default: return NULL;
  }
}

// На экранах логов и клавиатуры виджета сообщения нет.
static int em_index_for_screen(int screenId) {
  switch (screenId) {
    case SCREEN_ID_MAIN_SCREEN:      return 0;
    case SCREEN_ID_HAND_MODE_SCREEN: return 1;
    case SCREEN_ID_AUTO_MODE_SCREEN: return 2;
    case SCREEN_ID_OPTIONS_SCREEN:   return 3;
    default:                         return -1;
  }
}

static int last_error_message_cont = -1;   // -1 = ничего не показано



void show_error_message(const char* message) {
  show_error_message(message, false, EM_DEFAULT);
}

void show_error_message(const char* message, bool ynMode) {
  show_error_message(message, ynMode, EM_DEFAULT);
}

void show_error_message(const char* message, bool ynMode, error_message_type eType) {
  int id = em_index_for_screen(get_cur_screen_id());
  if (id < 0) {
    Serial.printf("[EM] no message widget on screen %d: %s\n", get_cur_screen_id(), message);
    return;
  }

  lv_obj_t* cont = get_em_container(id);
  if (cont == NULL) return;

  // Прошлое окно могло остаться на другом экране
  hide_all_error_messages();

  set_var_error_message_text(message);

  // true = СКРЫТЬ. Режим "да/нет" прячет OK, режим OK прячет да/нет.
  set_var_error_message_set_ok(ynMode);
  set_var_error_message_set_yn(!ynMode);

  lv_obj_t* panel = get_em_panel(id);
  if (panel != NULL) {
    uint32_t bg = (eType == EM_DANGER) ? 0xE53935 : 0xffd700;
    lv_obj_set_style_bg_color(panel, lv_color_hex(bg), LV_PART_MAIN);
  }

  lv_obj_clear_flag(cont, LV_OBJ_FLAG_HIDDEN);
  last_error_message_cont = id;

  Serial.printf("[EM] shown on %d: %s\n", id, message);
}



void hide_error_message() {
  hide_error_message_by_id(last_error_message_cont);
  last_error_message_cont = -1;
}

void hide_error_message_by_id(int id) {
  lv_obj_t* cont = get_em_container(id);
  if (cont == NULL) return;

  lv_obj_add_flag(cont, LV_OBJ_FLAG_HIDDEN);
}

void hide_all_error_messages() {
  for (int i = 0; i < ERROR_MESSAGE_CONT_AMOUNT; i++) {
    hide_error_message_by_id(i);
  }
  last_error_message_cont = -1;
}


// Показано ли сейчас окно - пригодится, чтобы не открывать второе поверх
bool is_error_message_shown() {
  return last_error_message_cont >= 0;
}
