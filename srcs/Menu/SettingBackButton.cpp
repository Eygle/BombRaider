#include "State/StateManager.hpp"
#include "Menu/SettingBackButton.hpp"

namespace Menu
{
  SettingBackButton::SettingBackButton(SettingState *state) : state_(state), data_(Data::getInstance())
  {
    Graphic::ImagePosition  pos(368, 573, 434, 632);
    this->position_ = pos;
    this->initAffichage(Data::PREV_ARROW, Data::PREV_ARROW_OVER, Data::PREV_ARROW_CLICKED,this->position_);
  }
  SettingBackButton::~SettingBackButton()
  {
  }

  void SettingBackButton::action(char)
  {
    this->state_->save();
    this->data_->states->pop();
  }

  void SettingBackButton::update()
  {
  }

}
