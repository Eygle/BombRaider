# include "Menu/PauseState.hpp"

namespace Menu
{
  PauseState::PauseState()
  : layout_(0)
  {
    Data *data = Data::getInstance();

    SaveButton	*save = new SaveButton;
    SwitchStateButton *quit = new SwitchStateButton(data->states, true, State::ARCADE, true);
    SwitchStateButton	*back_to_game = new SwitchStateButton(data->states, true, State::ARCADE);
    Graphic::ImagePosition	layoutp(540,200,825,570);
    Graphic::GuiImage		layout(layoutp,  &(data->imgs[Data::LAYOUT_PAUSE]));

    this->saveButton_ = save;
    this->initButton(save,data->db.getText(data->gameSettings.language, "button_save"),
		     560, 230, 805, 300);
    this->initButton(quit,data->db.getText(data->gameSettings.language, "button_quit"),
		     560, 360, 805, 430);
    this->initButton(back_to_game,data->db.getText(data->gameSettings.language, "button_back_to_game"),
		     560, 490, 805, 550);
    this->focus_ = this->buttons_.begin();
    this->setBackground(Data::BG_MENU);
  }

  PauseState::~PauseState()
  {
  }

  void	PauseState::init()
  {
    this->saveButton_->init(this->infos_);
  }

  void	PauseState::draw()
  {
    this->background_.draw();
    this->layout_.draw();
    this->drawButton();
  }

  void	PauseState::update()
  {
    while (!(this->events_->mouseEmpty()))
      {
	std::list<AButton *>::iterator it;
	Input::s_mouseEvent mouse = this->events_->popMouse();
	if ((it = this->findButtons(mouse.pos.first,mouse.pos.second)) != this->buttons_.end())
	  {
	    if (mouse.clic == gdl::Mouse::Left)
	      {
		if (mouse.mouseState == Input::RELEASE)
		  (*it)->action(0);
		else if (mouse.mouseState == Input::PRESSED)
		  (*it)->activatePress();
		else
		  (*it)->activateHover();
	      }
	    break;
	  }
      }

    while (!(this->events_->keyEmpty()))
      {
	Input::Event event = this->events_->popKey();
	if ((event.getKeys() == Input::Escape || event.getKeys() == Input::MidleB1
	     || event.getKeys() == Input::MidleB2)
	    && event.getState() == Input::RELEASE)
	  Data::getInstance()->states->pop();
      }
    this->events_->emptyKey();
    this->events_->emptyMouse();
  }

 void	PauseState::reset()
  {
  }
}
