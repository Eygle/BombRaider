#ifndef __SETTINGSTATE__
#define __SETTINGSTATE__

#include <list>

#include "MenuState.hpp"
#include "CheckBoxMap.hpp"
#include "CheckBoxLanguage.hpp"
#include "SoundSwitcher.hpp"

namespace Menu
{
  class SettingState : public MenuState
  {
  private :
    std::list<SoundSwitcher *>	soundSwitcher_;
    SoundSwitcher		*switcherFocus_;
    Graphic::GuiImage		layout_;
  public:
    SettingState();
    ~SettingState();

    virtual void	draw();
    virtual void	update();
    virtual void	reset();
    SoundSwitcher	*findSwitcher(int x, int y);
    void		save();
  };
};

#endif
