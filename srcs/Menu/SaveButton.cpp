#include "Menu/SaveButton.hpp"

namespace Menu
{
  SaveButton::SaveButton()
  {
    this->initAffichage(Data::BG_BUTTON, Data::BG_BUTTON_OVER, Data::BG_BUTTON_CLICKED, this->position_);
  }

  SaveButton::~SaveButton()
  {
  }

  void	SaveButton::init(GameInfo *gameInfo)
  {
    this->gameInfo_ = gameInfo;
  }

  void	SaveButton::update()
  {
  }

  void	SaveButton::action(char)
  {
    this->gameInfo_->save();
  }
}
