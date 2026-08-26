static lv_obj_t* selection_dropbox() {return objects.selection_dropbox;}

static int selected_dose = 0;

void fetch_for_selection() {
  if (selection_dropbox() == NULL) return;

  int cur_preset_amount = get_var_cur_preset_amount();

  if (cur_preset_amount <= 0) {
    clear_selection_dropbox();
    return;
  }

  String ans;
  for (int i = 0; i < cur_preset_amount; i++) {
    paramPresetStruct *cur_preset = get_var_preset(i);

    if (i > 0) ans += "\n";
    ans += cur_preset -> name;
  }

  lv_dropdown_set_options(selection_dropbox(), ans.c_str());
  selected_dose = 0;
  select_change_dose();
  lv_obj_clear_state(selection_dropbox(), LV_STATE_DISABLED);
}

void select_change_dose() {
  selected_dose = lv_dropdown_get_selected(selection_dropbox());
  paramPresetStruct *cur_preset = get_var_preset(selected_dose);

  set_var_min_weight(cur_preset -> min);
  set_var_max_weight(cur_preset -> max);
}

void clear_selection_dropbox() {
  if (selection_dropbox() == NULL) return;

  lv_dropdown_set_options(selection_dropbox(), "None");
  lv_obj_add_state(selection_dropbox(), LV_STATE_DISABLED);
}