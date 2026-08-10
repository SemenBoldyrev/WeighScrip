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