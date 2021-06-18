//
// Created by florian on 18.06.21.
//

#include "TimeSelector.h"


using namespace Pinetime::Applications::Screens;
TimeSelector::TimeSelector(int first, int second, lv_event_cb_t buttonHandler, bool showButtons, Screen* screen)
: buttonHandler{buttonHandler}, parentScreen{screen} {
  time = lv_label_create(lv_scr_act(), nullptr);
  lv_obj_set_style_local_text_font(time, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &jetbrains_mono_76);
  lv_obj_set_style_local_text_color(time, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_GRAY);
  
  lv_label_set_text_fmt(time, "%02d:%02d", first, second);
  
  lv_obj_align(time, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 0, -20);
  
  if (showButtons) {
    this->showButtons();
  }
  
  
}

void TimeSelector::showButtons() {
  btnMinutesUp = lv_btn_create(lv_scr_act(), nullptr);
  btnMinutesUp->user_data = parentScreen;
  lv_obj_set_event_cb(btnMinutesUp, buttonHandler);
  lv_obj_align(btnMinutesUp, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 20, -80);
  lv_obj_set_height(btnMinutesUp, 40);
  lv_obj_set_width(btnMinutesUp, 60);
  txtMUp = lv_label_create(btnMinutesUp, nullptr);
  lv_label_set_text(txtMUp, "+");
  
  btnMinutesDown = lv_btn_create(lv_scr_act(), nullptr);
  btnMinutesDown->user_data = parentScreen;
  lv_obj_set_event_cb(btnMinutesDown, buttonHandler);
  lv_obj_align(btnMinutesDown, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 20, +40);
  lv_obj_set_height(btnMinutesDown, 40);
  lv_obj_set_width(btnMinutesDown, 60);
  txtMDown = lv_label_create(btnMinutesDown, nullptr);
  lv_label_set_text(txtMDown, "-");
  
  btnSecondsUp = lv_btn_create(lv_scr_act(), nullptr);
  btnSecondsUp->user_data = parentScreen;
  lv_obj_set_event_cb(btnSecondsUp, buttonHandler);
  lv_obj_align(btnSecondsUp, lv_scr_act(), LV_ALIGN_IN_RIGHT_MID, 10, -80);
  lv_obj_set_height(btnSecondsUp, 40);
  lv_obj_set_width(btnSecondsUp, 60);
  txtSUp = lv_label_create(btnSecondsUp, nullptr);
  lv_label_set_text(txtSUp, "+");
  
  btnSecondsDown = lv_btn_create(lv_scr_act(), nullptr);
  btnSecondsDown->user_data = parentScreen;
  lv_obj_set_event_cb(btnSecondsDown, buttonHandler);
  lv_obj_align(btnSecondsDown, lv_scr_act(), LV_ALIGN_IN_RIGHT_MID, 10, +40);
  lv_obj_set_height(btnSecondsDown, 40);
  lv_obj_set_width(btnSecondsDown, 60);
  txtSDown = lv_label_create(btnSecondsDown, nullptr);
  lv_label_set_text(txtSDown, "-");
  
}

void TimeSelector::hideButtons() {
  lv_obj_del(btnSecondsDown);
  btnSecondsDown = nullptr;
  lv_obj_del(btnSecondsUp);
  btnSecondsUp = nullptr;
  lv_obj_del(btnMinutesDown);
  btnMinutesDown = nullptr;
  lv_obj_del(btnMinutesUp);
  btnMinutesUp = nullptr;
}

void TimeSelector::setTime(int first, int second) {
  lv_label_set_text_fmt(time, "%02d:%02d", first, second);
}
