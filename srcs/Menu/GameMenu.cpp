#include "Data.hpp"
#include "Menu/PlayerSwitcher.hpp"
#include "Menu/AISwitcher.hpp"
#include "Menu/MapSizeSwitcher.hpp"
#include "Menu/AIDificultySwitcher.hpp"
#include "Menu/FrequencySwitcher.hpp"
#include "Menu/ProfilInput.hpp"
#include "Menu/GameMenu.hpp"
#include "Menu/GameMenuNext.hpp"
#include "Menu/SwitchStateButton.hpp"

namespace Menu
{
  GameMenu::GameMenu() :  layout_(0) ,  switcherFocus_(0), profilFocus_(0), profilLastFocus_(0)
  {
    Data *data = Data::getInstance();
    Graphic::ImagePosition	layoutp(332,207,1023,648);
    Graphic::GuiImage		layout(layoutp, &(data->imgs[Data::LAYOUT_OPTION]));
    SwitchStateButton		*back = new SwitchStateButton(data->states, true, State::ARCADE);

    Graphic::ImagePosition	pos(365, 555, 425, 615);
    this->initButton(back, "", 365, 555, 425, 615);
    back->initAffichage(Data::PREV_ARROW, Data::PREV_ARROW_OVER, Data::PREV_ARROW_CLICKED, pos);
    this->setBackground(Data::BG_MENU);
    this->layout_ = layout;
    this->initSwitcher(this->switchers_);
    this->initProfilInput(this->profil_);
    GameMenuNext *next = new GameMenuNext(this);
    this->buttons_.push_back(next);
    //this->buttons_.push_back(back);
  }

  GameMenu::~GameMenu()
  {
  }

  void GameMenu::update()
  {
    while (!(this->events_->mouseEmpty()))
      {
	std::list<AButton *>::iterator it;
	Input::s_mouseEvent mouse = this->events_->popMouse();
	if (mouse.clic == gdl::Mouse::Left && mouse.mouseState == Input::PRESSED)
	    {
	      if (this->switcherFocus_)
		  this->switcherFocus_->modifieValue(mouse.pos.first);
	      else if ((this->switcherFocus_ = this->findSwitcher(mouse.pos.first, mouse.pos.second)))
		this->switcherFocus_->modifieValue(mouse.pos.first);
	      else if ((it = this->findButtons(mouse.pos.first,mouse.pos.second)) != this->buttons_.end())
		(*it)->activatePress();
	    }
	else if (mouse.clic == gdl::Mouse::Left && mouse.mouseState == Input::RELEASE)
	  {
	    this->switcherFocus_ = 0;
	    if ((it = this->findButtons(mouse.pos.first,mouse.pos.second)) != this->buttons_.end())
	      (*it)->action(0);
	    this->profilFocus_ = this->findInput(mouse.pos.first, mouse.pos.second);
	    if (this->profilFocus_)
	      {
		this->profilFocus_->activatePress();
		if (this->profilLastFocus_ && this->profilLastFocus_ != this->profilFocus_)
		  this->profilLastFocus_->desactivatePress();
		this->profilLastFocus_ = this->profilFocus_;
	      }
	    break;
	  }
	else
	  {
	    if ((it = this->findButtons(mouse.pos.first,mouse.pos.second)) != this->buttons_.end())
	      (*it)->activateHover();
	  }
      }
    this->events_->emptyMouse();
    if (this->profilFocus_)
      {
	while (!(this->events_->keyEmpty()))
	  {
	    Input::Event key = this->events_->popKey();
	    if (key.getState() == Input::RELEASE)
	      {
		Input::Key value = key.getKeys();
		if (value >= Input::A && value <= Input::Z)
		  {
		    char c = 65 + static_cast<int>(value);
		    this->profilFocus_->action(c);
		  }
		else if (value == Input::Back)
		  this->profilFocus_->action('\b');
		else if (value == Input::Space)
		  this->profilFocus_->action(' ');
		break ;
	      }
	  }
      }
    this->events_->emptyKey();
  }

  void GameMenu::draw()
  {
    this->background_.draw();
    this->layout_.draw();
    this->drawSwitcher();
    this->drawProfil();
    this->drawButton();
  }

  void GameMenu::reset()
  {
  }

  void	GameMenu::drawSwitcher()
  {
    std::list<Switcher *>::iterator it = this->switchers_.begin();
    std::list<Switcher *>::iterator end = this->switchers_.end();

    while (it != end)
      {
	(*it)->draw();
	++it;
      }
  }

  void	GameMenu::drawProfil()
  {
    std::list<ProfilInput *>::iterator it = this->profil_.begin();
    std::list<ProfilInput *>::iterator end = this->profil_.end();
    unsigned int		i = 0;
    while (it != end && i < *(this->nbPlayer_))
      {
	(*it)->draw();
	 ++it;
	 ++i;
       }
  }

  void GameMenu::initSwitcher(std::list<Switcher *> &switcher)
  {
    PlayerSwitcher *player = new PlayerSwitcher(497, 277, 678, 297);
    this->nbPlayer_ = player->getNbPlayer();
    AISwitcher *ai = new AISwitcher(774, 277, 953, 297);
    AIDificultySwitcher *dif = new AIDificultySwitcher(551, 314,953, 334);
    MapSizeSwitcher *map = new MapSizeSwitcher(551, 360,953, 380);
    FrequencySwitcher *bonus = new FrequencySwitcher(551, 406,953, 426, true);
    FrequencySwitcher *caiss = new FrequencySwitcher(551, 452,953, 472, false);


    switcher.push_back(dif);
    switcher.push_back(player);
    switcher.push_back(ai);
    switcher.push_back(map);
    switcher.push_back(bonus);
    switcher.push_back(caiss);
  }

  Switcher	*GameMenu::findSwitcher(int x, int y)
  {
    std::list<Switcher *>::iterator it = this->switchers_.begin();
    std::list<Switcher *>::iterator end = this->switchers_.end();
    while (it != end)
      {
	if ((*it)->isSelected(x, y))
	  return (*it);
	++it;
      }
    return (0);
  }

  ProfilInput	*GameMenu::findInput(int x, int y)
  {
    std::list<ProfilInput *>::iterator it = this->profil_.begin();
    std::list<ProfilInput *>::iterator end = this->profil_.end();
    unsigned int		i = 0;
    while (it != end &&  i < *(this->nbPlayer_))
      {
	if ((*it)->isIn(x, y))
	  return (*it);
	++it;
	++i;
      }
    return (0);
  }

  void	GameMenu::initProfilInput(std::list<ProfilInput *> &input)
  {
    Data *datas = Data::getInstance();
    std::string str = Data::getInstance()->db.getText(datas->gameSettings.language, "player");

    ProfilInput *player1 = new ProfilInput(0);
    player1->initInput(str + "1", 500);
    ProfilInput *player2 = new ProfilInput(1);
    player2->initInput(str + "2", 530);
    ProfilInput *player3 = new ProfilInput(2);
    player3->initInput(str + "3", 560);
    ProfilInput *player4 = new ProfilInput(3);
    player4->initInput(str + "4", 590);
    input.push_back(player1);
    input.push_back(player2);
    input.push_back(player3);
    input.push_back(player4);
  }

  void	GameMenu::updateSwitcher()
  {
    std::list<Switcher *>::iterator it = this->switchers_.begin();
    std::list<Switcher *>::iterator end = this->switchers_.end();
    while (it != end)
      {
	(*it)->update();
	++it;
      }
  }

  void	GameMenu::updateInput()
  {
    std::list<ProfilInput *>::iterator it = this->profil_.begin();
    std::list<ProfilInput *>::iterator end = this->profil_.end();
    unsigned int		i = 0;
    while (it != end &&  i < *(this->nbPlayer_))
      {
	(*it)->update();
	++it;
	++i;
      }
  }

  void	GameMenu::saveValue()
  {
    this->updateSwitcher();
    this->updateInput();
  }

  void	GameMenu::init()
  {
    std::list<ProfilInput *>::iterator it = this->profil_.begin();
    std::list<ProfilInput *>::iterator end = this->profil_.end();

    while (it != end)
      {
	(*it)->init(this->infos_);
	++it;
      }
  }

}
