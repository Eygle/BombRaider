#include "Menu/SwitchStateButton.hpp"

namespace Menu
{
  SwitchStateButton::SwitchStateButton(State::StateManager *stateManager, bool pop, State::e_State stat, bool popAll)
    : stateManager_(stateManager), pop_(pop), state_(stat), popAll_(popAll)
  {
    this->initAffichage(Data::BG_BUTTON, Data::BG_BUTTON_OVER, Data::BG_BUTTON_CLICKED, this->position_);
  }

  SwitchStateButton::~SwitchStateButton()
  {
  }

  void SwitchStateButton::action(char)
  {
    if (this->popAll_)
      this->stateManager_->backToMenu();
    else if (this->pop_)
      this->stateManager_->pop();
    else
      this->stateManager_->push(state_);
  }

  void SwitchStateButton::update()
  {
  }
}
