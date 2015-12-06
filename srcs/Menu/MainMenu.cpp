#include <GDL/Image.hpp>

#include "Menu/MainMenu.hpp"
#include "Menu/SimpleButton.hpp"
#include "Menu/SwitchStateButton.hpp"

#include "Character/Player.hpp"

#include "Data.hpp"

namespace Menu
{
  MainMenu::MainMenu()
  {
    Data	*data = Data::getInstance();
    SwitchStateButton *play = new SwitchStateButton(data->states, false, State::GAMEMENU);
    SwitchStateButton *ranking = new SwitchStateButton(data->states, false, State::RANKING);
    SwitchStateButton *setting = new SwitchStateButton(data->states, false, State::SETTING);
    SwitchStateButton *credits = new SwitchStateButton(data->states, false, State::CREDITS);
    SwitchStateButton *quit = new SwitchStateButton(data->states, true, State::ARCADE);
    this->loadButton_ = new LoadButton;
    this->initButton(play,data->db.getText(data->gameSettings.language, "button_play"),
		     512, 225, 853, 300);
    this->initButton(this->loadButton_,data->db.getText(data->gameSettings.language, "button_load"),
		     512, 325, 853, 400);
    this->initButton(ranking,data->db.getText(data->gameSettings.language, "button_ranking"),
		     512, 425, 853, 500);
    this->initButton(setting,data->db.getText(data->gameSettings.language, "button_settings"),
		     100, 650, 400, 725);
    this->initButton(credits,data->db.getText(data->gameSettings.language, "button_credits"),
		     950, 550, 1265, 625);
    this->initButton(quit,data->db.getText(data->gameSettings.language, "button_quit"),
		     950, 650, 1265, 725);
    this->focus_ = this->buttons_.begin();
    this->setBackground(Data::BG_MENU);
  }

  MainMenu::~MainMenu()
  {
  }

  void	MainMenu::update()
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
    this->events_->emptyKey();
    this->events_->emptyMouse();
  }

  void	MainMenu::draw()
  {
    this->background_.draw();
    this->drawButton();
  }

  void	MainMenu::init()
  {
    this->loadButton_->init(this->infos_);
  }
}
