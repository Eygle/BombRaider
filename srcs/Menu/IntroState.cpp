#include "Menu/IntroState.hpp"
#include "Menu/SimpleButton.hpp"

namespace Menu
{
  IntroState::IntroState()
  {
    SimpleButton *play = new SimpleButton;

    this->pageNbr_ = 0;
    this->page_[0] = Data::INTRO_1;
    this->page_[1] = Data::INTRO_2;
    this->page_[2] = Data::INTRO_3;
    this->setBackground(Data::INTRO_1);

    this->initButton(play, "", 0, 0, 0, 0);
    this->focus_ = this->buttons_.begin();
  }

  IntroState::~IntroState()
  {
  }

  void	IntroState::update()
  {
    while (!this->events_->keyEmpty())
    {
      Input::Event event = this->events_->popKey();
      if (event.getKeys() == Input::Escape && event.getState() == Input::RELEASE)
	Data::getInstance()->states->pop();
      else if ((event.getKeys() == Input::Space || event.getKeys() == Input::Return)
	       && event.getState() == Input::RELEASE)
	{
	  if (this->pageNbr_ == 2)
	    {
	      this->pageNbr_ = 0;
	      this->setBackground(this->page_[0]);
	      Data::getInstance()->states->pop();
	    }
	  else
	    {
	      this->pageNbr_++;
	      this->setBackground(this->page_[this->pageNbr_]);
	    }
	}
    }
    this->events_->emptyKey();
    this->events_->emptyMouse();
  }

  void	IntroState::draw()
  {
    this->background_.draw();
    this->drawButton();
  }
}
