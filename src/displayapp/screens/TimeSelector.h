
#include "../LittleVgl.h"
#include "Screen.h"

namespace Pinetime::Applications::Screens {
  class TimeSelector {
  public:
    TimeSelector(int first = 0, int second = 0, lv_event_cb_t buttonHandler = nullptr, bool showButtons = true, Screen* screen = nullptr);
    
    void showButtons();
    
    void hideButtons();
    
    void setTime(int first, int second);
    
    
    //keep those public to allow users maximum flexibility
    lv_obj_t* time, * btnMinutesUp, * btnMinutesDown, * btnSecondsUp, * btnSecondsDown, * txtMUp,
        * txtMDown, * txtSUp, * txtSDown;
    
    lv_event_cb_t buttonHandler;
    Screen* parentScreen;
  };
}

