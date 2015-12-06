#include "Menu/CreditState.hpp"

namespace Menu
{
  CreditState::CreditState()
  {
    this->setBackground(Data::CREDITS);
  }

  CreditState::~CreditState()
  {
  }

  void	CreditState::draw()
  {
    this->background_.draw();
  }

  void	CreditState::update()
  {
    while (!this->events_->keyEmpty())
    {
      Input::Event event = this->events_->popKey();
      if (event.getKeys() == Input::Escape && event.getState() == Input::RELEASE)
	Data::getInstance()->states->pop();
    }
  }
}
