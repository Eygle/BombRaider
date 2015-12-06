#include "Menu/SelectPlayerArrayButton.hpp"

namespace Menu
{
  SelectPlayerArrayButton::SelectPlayerArrayButton(int id, bool prev)
    : AButton(id)
  {
    if (prev)
      this->initAffichage(Data::PREV_ARROW, Data::PREV_ARROW_OVER, Data::PREV_ARROW_CLICKED, this->position_);
    else
      this->initAffichage(Data::NEXT_ARROW, Data::NEXT_ARROW_OVER, Data::NEXT_ARROW_CLICKED, this->position_);
  }

  SelectPlayerArrayButton::~SelectPlayerArrayButton()
  {
  }

  void	SelectPlayerArrayButton::action(char)
  {
  }

  void	SelectPlayerArrayButton::update()
  {
  }
}
