#define SPINERS_AMOUNT 2


static lv_obj_t* get_spiner_container(int i) {
  switch (i) { // why they are not getting names?
    case 0:  return objects.obj11__spiner_container;   // options
    case 1:  return objects.obj13__spiner_container;   // keyboard
    default: return NULL;
  }
}

void show_spiner(int spinerId) {
  lv_obj_t* cont = get_spiner_container(spinerId);
  if (cont == NULL) {
    Serial.printf("!! no spiner with id %d\n", spinerId);
    return;
  }

  lv_obj_clear_flag(cont, LV_OBJ_FLAG_HIDDEN);

  lv_refr_now(NULL);
}


void hide_spiner(int spinerId) {
  lv_obj_t* cont = get_spiner_container(spinerId);
  if (cont == NULL) return;

  lv_obj_add_flag(cont, LV_OBJ_FLAG_HIDDEN);
}


void hide_all_spiners() {
  for (int i = 0; i < SPINERS_AMOUNT; i++) {
    hide_spiner(i);
  }
}
