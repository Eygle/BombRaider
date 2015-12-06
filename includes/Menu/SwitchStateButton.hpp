#ifndef __SWITCHSTATEBUTTON__
#define __SWITCHSTATEBUTTON__

#include "State/StateManager.hpp"
#include "Menu/AButton.hpp"

namespace Menu
{
  class SwitchStateButton : public AButton
  {
  private :
    State::StateManager		*stateManager_;
    bool			pop_;
    State::e_State		state_;
    bool			popAll_;

  public :
    SwitchStateButton(State::StateManager *stateManager, bool pop, State::e_State stat,
		      bool popAll = false);
    ~SwitchStateButton();
    virtual void action(char c = 0);
    virtual void update();
  };

};

#endif
