#pragma once

#include <memory>
#include "Screen.h"
#include "components/datetime/DateTimeController.h"
#include "systemtask/SystemTask.h"
#include "../LittleVgl.h"

#include "components/timer/TimerController.h"
#include "TimeSelector.h"


namespace Pinetime::Applications::Screens {
  
  
  class Timer : public Screen {
  public:
    
    enum class Modes {
      Normal, Done
    };
    
    Timer(DisplayApp* app, Controllers::TimerController& timerController);
    
    ~Timer() override;
    
    bool Refresh() override;
    
    void setDone();
    
    void OnButtonEvent(lv_obj_t* obj, lv_event_t event);
  
  private:
    
    bool running;
    uint8_t secondsToSet = 0;
    uint8_t minutesToSet = 0;
    Controllers::TimerController& timerController;
    
    
    lv_obj_t * btnPlayPause, * txtPlayPause;
    std::unique_ptr<TimeSelector> timeSelector;
  };
}