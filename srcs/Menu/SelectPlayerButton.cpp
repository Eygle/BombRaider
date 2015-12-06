#include "Menu/SelectPlayerButton.hpp"

namespace Menu
{
  SelectPlayerButton::SelectPlayerButton(int id)
    : AButton(id)
  {
    this->initAffichage(Data::BG_BUTTON, Data::BG_BUTTON_OVER, Data::BG_BUTTON_CLICKED, this->position_);
  }

  SelectPlayerButton::~SelectPlayerButton()
  {
  }

  void	SelectPlayerButton::update()
  {
  }

  void	SelectPlayerButton::action(char)
  {
  }
}
