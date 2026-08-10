void get_debug_info(bool heapInf, bool flasshInf) {
  Serial.println("========================================");

  if (heapInf)
  {
    show_heap_info();
  }

  if (flasshInf)
  {
    show_flash_inf();
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

// Сколько байт стека у текущей задачи ОСТАЛОСЬ в самый худший момент.
// Если значение падает к нулю - будет "Stack canary watchpoint triggered".
void show_stack_info(const char* tag) {
  // В ESP-IDF (в отличие от «ванильного» FreeRTOS) эта функция возвращает
  // уже БАЙТЫ, а не слова. Умножать на 4 не нужно.
  UBaseType_t freeBytes = uxTaskGetStackHighWaterMark(NULL);
  Serial.printf("[STACK] %-24s free: %u bytes\n", tag, (unsigned)freeBytes);
}