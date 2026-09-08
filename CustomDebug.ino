void get_debug_info(bool heapInf, bool flasshInf, bool looptask, bool lvglMem) {
  //Serial.println("========================================");

  if (heapInf)
  {
    show_heap_info();
  }

  if (flasshInf)
  {
    show_flash_inf();
  }

  if (looptask) {
    show_looptask_info();
  }

  if(lvglMem) {
    show_lvgl_mem_info_timer();
  }
}

void show_heap_info() {
  Serial.printf("8BIT: %d", heap_caps_get_free_size(MALLOC_CAP_8BIT));
  Serial.println();
  Serial.printf("32BIT: %d", heap_caps_get_free_size(MALLOC_CAP_32BIT));
  Serial.println();
  Serial.printf("DMA: %d", heap_caps_get_free_size(MALLOC_CAP_DMA));
  Serial.println();
  Serial.printf("SPIRAM: %d", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
  Serial.println();
}

void show_flash_inf() {

}

void show_looptask_info() {
  // временная диагностика: следим за запасом стека loopTask
  static uint32_t lastStackLog = 0;
  if (millis() - lastStackLog > 2000) {
    lastStackLog = millis();
    show_stack_info("loop");
  }
}

void show_lvgl_mem_info_timer() {
  // временная диагностика: следим за запасом стека loopTask
  static uint32_t lastStackLog = 0;
  if (millis() - lastStackLog > 2000) {
    lastStackLog = millis();
    show_lvgl_mem_info("loop");
  }
}

// Сколько байт стека у текущей задачи ОСТАЛОСЬ в самый худший момент.
// Если значение падает к нулю - будет "Stack canary watchpoint triggered".
void show_stack_info(const char* tag) {
  // В ESP-IDF (в отличие от «ванильного» FreeRTOS) эта функция возвращает
  // уже БАЙТЫ, а не слова. Умножать на 4 не нужно.
  UBaseType_t freeBytes = uxTaskGetStackHighWaterMark(NULL);
  Serial.printf("[STACK] %-24s free: %u bytes\n", tag, (unsigned)freeBytes);
}

// Состояние ВНУТРЕННЕЙ кучи LVGL (это не общая куча ESP32!).
// Если used_pct подбирается к 100 - LV_MEM_SIZE в lv_conf.h мал.
void show_lvgl_mem_info(const char* tag) {
  static bool once = false;
  if (!once) {
    once = true;
    Serial.printf("[LVGL]  version %d.%d.%d\n",
                  LVGL_VERSION_MAJOR, LVGL_VERSION_MINOR, LVGL_VERSION_PATCH);
#ifdef LV_MEM_SIZE
    Serial.printf("[LVGL]  LV_MEM_SIZE = %u B\n", (unsigned)LV_MEM_SIZE);
#else
    Serial.println("[LVGL]  LV_MEM_SIZE not defined here");
#endif
  }

  // lv_mem_monitor() есть всегда; если LVGL работает через clib malloc,
  // total_size вернётся нулём - тогда смотрим на [HEAP].
  lv_mem_monitor_t mon;
  lv_mem_monitor(&mon);
  Serial.printf("[LVMEM] %-18s total: %u B  used: %u%%  free: %u B  biggest: %u B  frag: %u%%\n",
                tag, (unsigned)mon.total_size, (unsigned)mon.used_pct,
                (unsigned)mon.free_size, (unsigned)mon.free_biggest_size,
                (unsigned)mon.frag_pct);

  Serial.printf("[HEAP]  %-18s free: %u B  biggest: %u B\n", tag,
                (unsigned)heap_caps_get_free_size(MALLOC_CAP_8BIT),
                (unsigned)heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
  Serial.flush();
}

void show_in_console(const char* key, const char* message)
{
  char tag[30];
  make_tag(key, tag, sizeof(tag));

  Serial.print(tag);
  Serial.print("  ");
  Serial.println(message);
}

// Метка времени для строки лога. Нужна и системному журналу, и журналу
// взвешиваний, поэтому вынесена отдельно.
// Внутри файла двоеточия разрешены - ограничение только для ИМЁН файлов.
void build_log_timestamp(char* out, size_t size)
{
  struct tm t;

  if (getLocalTime(&t, 0) && t.tm_year >= (2020 - 1900)) {
    snprintf(out, size, "%04d-%02d-%02d %02d:%02d:%02d",
             t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
             t.tm_hour, t.tm_min, t.tm_sec);
  }
  else {
    // Часы ещё не выставлены - пишем время от включения платы
    snprintf(out, size, "uptime %lus", (unsigned long)(millis() / 1000));
  }
}

void show_in_console_save_in_log(const char* key, const char* message)
{
  show_in_console(key, message);

  char stamp[24];
  char tag[30];

  build_log_timestamp(stamp, sizeof(stamp));
  make_tag(key, tag, sizeof(tag));

  save_in_system_log(stamp, tag, message);
}

void make_tag(const char* text, char* out, size_t size) {
  if (size < 3) { if (size) out[0] = '\0'; return; }

  size_t i = 0;
  out[i++] = '[';

  // size - 2: оставляем место под ']' и завершающий ноль
  for (const char* p = text; *p != '\0' && i < size - 2; p++) {
    out[i++] = toupper((unsigned char)*p);
  }

  out[i++] = ']';
  out[i]   = '\0';
}