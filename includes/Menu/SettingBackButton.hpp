#ifndef __SETTINGBACKBUTTON__
#define __SETTINGBACKBUTTON__

#include "SettingState.hpp" // GameMenu
#include "AButton.hpp" // AButton
#include "Data.hpp" // Data

namespace Menu
{
  class SettingBackButton : public AButton 
  {
  private :
    SettingState	*state_;
    Data		*data_;
  public :
    SettingBackButton(SettingState	*state);
    ~SettingBackButton();
    virtual void action(char c);
    virtual void update();
  };
};

#endif
