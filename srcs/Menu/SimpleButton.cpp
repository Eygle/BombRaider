#include "Menu/SimpleButton.hpp"

namespace Menu
{
  SimpleButton::SimpleButton()
  {
    this->isPressed_ =  false;
  }
  SimpleButton::~SimpleButton(){}

  void  SimpleButton::action(char)
  {
  }

  void  SimpleButton::update()
  {
  }

  void	SimpleButton::draw()
  {
    if (this->isPressed_)
      this->hover_.draw();
    else
      this->normal_.draw();
    this->text_.draw();
  }
}
