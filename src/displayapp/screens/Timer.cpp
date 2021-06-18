#include "Timer.h"

#include "Screen.h"
#include "Symbols.h"
#include "lvgl/lvgl.h"


using namespace Pinetime::Applications::Screens;


static void btnEventHandler(lv_obj_t* obj, lv_event_t event) {
  Timer* screen = static_cast<Timer*>(obj->user_data);
  screen->OnButtonEvent(obj, event);
}


Timer::Timer(DisplayApp* app, Controllers::TimerController& timerController)
    : Screen(app),
      running{true},
      timerController{timerController} {
  
  
  btnPlayPause = lv_btn_create(lv_scr_act(), nullptr);
  btnPlayPause->user_data = this;
  lv_obj_set_event_cb(btnPlayPause, btnEventHandler);
  lv_obj_align(btnPlayPause, lv_scr_act(), LV_ALIGN_IN_BOTTOM_MID, 0, -10);
  lv_obj_set_height(btnPlayPause, 40);
  txtPlayPause = lv_label_create(btnPlayPause, nullptr);
  
  uint32_t seconds = timerController.GetTimeRemaining() / 1000;
  timeSelector =
      std::make_unique<TimeSelector>(TimeSelector(seconds / 60, seconds % 60, btnEventHandler, false, this));

  if (timerController.IsRunning()) {
    lv_label_set_text(txtPlayPause, Symbols::pause);
  } else {
    lv_label_set_text(txtPlayPause, Symbols::play);
    timeSelector->showButtons();
  }
  
  
  
}

Timer::~Timer() {
  lv_obj_clean(lv_scr_act());
  
}

bool Timer::Refresh() {
  if (timerController.IsRunning()) {
    uint32_t seconds = timerController.GetTimeRemaining() / 1000;
    timeSelector->setTime(seconds / 60, seconds % 60);
  }
  return running;
}

void Timer::OnButtonEvent(lv_obj_t* obj, lv_event_t event) {
  if (event == LV_EVENT_CLICKED) {
    if (obj == btnPlayPause) {
      if (timerController.IsRunning()) {
        lv_label_set_text(txtPlayPause, Symbols::play);
        uint32_t seconds = timerController.GetTimeRemaining() / 1000;
        minutesToSet = seconds / 60;
        secondsToSet = seconds % 60;
        timerController.StopTimer();
        timeSelector->showButtons();
        
      } else if (secondsToSet + minutesToSet > 0) {
        lv_label_set_text(txtPlayPause, Symbols::pause);
        timerController.StartTimer((secondsToSet + minutesToSet * 60) * 1000);
        timeSelector->hideButtons();
        
      }
    } else {
      if (!timerController.IsRunning()) {
        if (obj == timeSelector->btnMinutesUp) {
          if (minutesToSet >= 59) {
            minutesToSet = 0;
          } else {
            minutesToSet++;
          }
          timeSelector->setTime(minutesToSet, secondsToSet);
          
        } else if (obj == timeSelector->btnMinutesDown) {
          if (minutesToSet == 0) {
            minutesToSet = 59;
          } else {
            minutesToSet--;
          }
          timeSelector->setTime(minutesToSet, secondsToSet);
          
        } else if (obj == timeSelector->btnSecondsUp) {
          if (secondsToSet >= 59) {
            secondsToSet = 0;
          } else {
            secondsToSet++;
          }
          timeSelector->setTime(minutesToSet, secondsToSet);
          
        } else if (obj == timeSelector->btnSecondsDown) {
          if (secondsToSet == 0) {
            secondsToSet = 59;
          } else {
            secondsToSet--;
          }
          timeSelector->setTime(minutesToSet, secondsToSet);
          
        }
      }
      
    }
    
  }
  
}


void Timer::setDone() {
  timeSelector->setTime(0, 0);
  lv_label_set_text(txtPlayPause, Symbols::play);
  secondsToSet = 0;
  minutesToSet = 0;
  timeSelector->showButtons();
}