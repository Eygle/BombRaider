#include <sstream>

#include "Champion/Champion.hpp"
#include "Menu/SelectPlayer.hpp"
#include "Menu/SelectPlayerButton.hpp"
#include "Menu/SelectPlayerArrayButton.hpp"
#include "Character/Player.hpp"
#include "Character/AI.hpp"
#include "Champion/Minion.hpp"
#include "State/Arcade.hpp"

#define X1 327
#define X2 492
#define DIFF 165

namespace Menu
{
  SelectPlayer::SelectPlayer(State::e_State idState)
    : id_(idState), init_(false), imgPos_(0, 0, 0, 0)
  {
    Data *datas = Data::getInstance();

    this->funPtr[0] = &SelectPlayer::prevPlayer;
    this->funPtr[1] = &SelectPlayer::nextPlayer;
    this->funPtr[2] = &SelectPlayer::goBack;
    this->funPtr[3] = &SelectPlayer::saveAndNext;

    this->imgPos_.setPos(311, 462, 327, 594);
    this->allSkillIcons_ = new Graphic::GuiImage(this->imgPos_, &datas->imgs[Data::ALL_SKILL_ICONS]);
    this->imgPos_.setPos(855, 462, 893, 495);
    this->skillIcon_ = new Graphic::GuiImage(this->imgPos_, &datas->imgs[Data::SKILL_ICON]);
    this->imgPos_.setPos(243, 175, 1101, 641);
    this->shadow_ = new Graphic::GuiImage(this->imgPos_, &datas->imgs[Data::SELECT_PLAYER_SHADOW]);
    this->imgPos_.setPos(256, 456, 506, 602);
    this->shadowText1_ = new Graphic::GuiImage(this->imgPos_, &datas->imgs[Data::SELECT_PLAYER_SHADOW_TEXT]);
    this->imgPos_.setPos(844, 456, 1089, 602);
    this->shadowText2_ = new Graphic::GuiImage(this->imgPos_, &datas->imgs[Data::SELECT_PLAYER_SHADOW_TEXT]);

    this->imgPos_.setPos(0, 0, 0, 0);

    unsigned int	textSize = 12;
    unsigned int	skillTextSize = 10;

    this->initTextFromString(this->profileName_, "Profile", this->centerText(583, "Profile", 14, 178), 191, 14);
    this->initTextFromString(this->hpTitle_,
    		     datas->db.getText(datas->gameSettings.language, "hp"),
    			     this->centerText(264,
    					      datas->db.getText(datas->gameSettings.language, "hp"),
    					      skillTextSize, 47), 462, skillTextSize);
    this->initTextFromString(this->manaTitle_,
    		     datas->db.getText(datas->gameSettings.language, "mana"),
    			     this->centerText(264,
    					      datas->db.getText(datas->gameSettings.language, "mana"),
    					      skillTextSize, 47), 478, skillTextSize);
    this->initTextFromString(this->powerTitle_,
    		     datas->db.getText(datas->gameSettings.language, "power"),
    			     this->centerText(264,
                                              datas->db.getText(datas->gameSettings.language, "power"),
                                              skillTextSize, 47), 496, skillTextSize);
    this->initTextFromString(this->defTitle_,
    		     datas->db.getText(datas->gameSettings.language, "defence"),
    			     this->centerText(264,
                                              datas->db.getText(datas->gameSettings.language, "defence"),
                                              skillTextSize, 47), 510, skillTextSize);
    this->initTextFromString(this->critTitle_,
    		     datas->db.getText(datas->gameSettings.language, "crit"),
    			     this->centerText(264,
                                              datas->db.getText(datas->gameSettings.language, "crit"),
                                              skillTextSize, 47), 527, skillTextSize);
    this->initTextFromString(this->resiTitle_,
    			     datas->db.getText(datas->gameSettings.language, "resi"),
    			     this->centerText(264,
                                              datas->db.getText(datas->gameSettings.language, "resi"),
                                              skillTextSize, 47), 546, skillTextSize);
    this->initTextFromString(this->rangeTitle_,
    		     datas->db.getText(datas->gameSettings.language, "range"),
    			     this->centerText(264,
                                              datas->db.getText(datas->gameSettings.language, "range"),
                                              skillTextSize, 47), 563, skillTextSize);
    this->initTextFromString(this->speedTitle_,
    		     datas->db.getText(datas->gameSettings.language, "speed"),
    			     this->centerText(264,
                                              datas->db.getText(datas->gameSettings.language, "speed"),
                                              skillTextSize, 47), 580, skillTextSize);

    this->initTextFromInt(this->hp_, 0, 406, 462, textSize);
    this->initTextFromInt(this->mana_, 0, 406, 478, textSize);
    this->initTextFromInt(this->power_, 0, 406, 496, textSize);
    this->initTextFromInt(this->def_, 0, 406, 512, textSize);
    this->initTextFromInt(this->crit_, 0, 406, 529, textSize);
    this->initTextFromInt(this->resi_, 0, 406, 546, textSize);
    this->initTextFromInt(this->range_, 0, 406, 563, textSize);
    this->initTextFromInt(this->speed_, 0, 406, 580, textSize);

    this->initTextFromString(this->skill_, "", 906, 465, textSize);

    SelectPlayerArrayButton *prevPlayer = new SelectPlayerArrayButton(0, true);
    SelectPlayerArrayButton *nextPlayer = new SelectPlayerArrayButton(1, false);
    SelectPlayerButton *back = new SelectPlayerButton(2);

    this->next_ = new SelectPlayerButton(3);

    this->initArrow(prevPlayer, 369, 384, 430, 439);
    this->initArrow(nextPlayer, 893, 384, 960, 439);

    bool	last = static_cast<int>(this->id_) - static_cast<int>(State::SELECTPLAYER1) + 1 == datas->gameSettings.nbrPlayers ? true : false;

    this->initButton(this->next_,
    		     datas->db.getText(datas->gameSettings.language,
    					    last ? "button_play" : "next"),
    		     844, 695, 1041, 751);
    this->initButton(back,
    		     datas->db.getText(datas->gameSettings.language, "button_back"),
    		     298, 695, 492, 751);

    this->focus_ = this->buttons_.begin();
    this->setBackground(Data::BG_MENU);
  }

  SelectPlayer::~SelectPlayer()
  {
    delete this->allSkillIcons_;
    delete this->skillIcon_;
    delete this->shadow_;
    delete this->shadowText1_;
    delete this->shadowText2_;
    delete this->next_;
  }

  void	SelectPlayer::initArrow(AButton *arrow, int x1, int y1, int x2, int y2)
  {
    arrow->setPosition(x1, y1, x2, y2);
    this->buttons_.push_back(arrow);
  }

  void	SelectPlayer::updateTextFromInt(gdl::Text &text, int val)
  {
    std::ostringstream oss;

    oss << val;
    text.setText(oss.str());
  }

  void	SelectPlayer::draw()
  {
    this->background_.draw();
    this->shadow_->draw();
    this->shadowText1_->draw();
    this->shadowText2_->draw();
    this->profileBackground_->draw();
    this->profileName_.draw();
    this->drawButton();
    this->hpTitle_.draw();
    this->manaTitle_.draw();
    this->critTitle_.draw();
    this->resiTitle_.draw();
    this->powerTitle_.draw();
    this->defTitle_.draw();
    this->rangeTitle_.draw();
    this->speedTitle_.draw();
    this->hpBar_->draw();
    this->manaBar_->draw();
    this->critBar_->draw();
    this->resiBar_->draw();
    this->powerBar_->draw();
    this->defBar_->draw();
    this->rangeBar_->draw();
    this->speedBar_->draw();
    this->hp_.draw();
    this->mana_.draw();
    this->crit_.draw();
    this->resi_.draw();
    this->power_.draw();
    this->def_.draw();
    this->range_.draw();
    this->speed_.draw();
    this->skill_.draw();
    this->championImg_->draw();
    this->allSkillIcons_->draw();
    this->skillIcon_->draw();
  }

  void	SelectPlayer::updateTexts()
  {
    Statistics	const &stats = (*this->champion)->getStats();
    Data *datas = Data::getInstance();

    this->updateTextFromInt(this->hp_, stats.get(Statistics::HP_MAX));
    this->updateTextFromInt(this->mana_, stats.get(Statistics::MANA_MAX));
    this->updateTextFromInt(this->crit_, stats.get(Statistics::CRITICAL));
    this->updateTextFromInt(this->resi_, stats.get(Statistics::RESILIENCE));
    this->updateTextFromInt(this->power_, stats.get(Statistics::POWER));
    this->updateTextFromInt(this->def_, stats.get(Statistics::DEFENSE));
    this->updateTextFromInt(this->range_, stats.get(Statistics::RANGE));
    this->updateTextFromInt(this->speed_, stats.get(Statistics::SPEED));

    std::string	skillText = datas->db.getText(datas->gameSettings.language,
    					      (*this->champion)->getSkillTag());
    this->skill_.setText(formatSkillText(skillText));
    if (this->infos_->players[this->id_ - State::SELECTPLAYER1]->getTrueProfile())
      {
	std::string name = this->infos_->players[this->id_ - State::SELECTPLAYER1]->getTrueProfile()->name;
	this->profileName_.setText(name);
	this->profileName_.setPosition(this->centerText(583, name, 14, 178), 191);
      }
  }

  void	SelectPlayer::updateStats()
  {
    Statistics	const &stats = (*this->champion)->getStats();

    this->hpBar_->setX2(X1 + (stats.get(Statistics::HP_MAX) / static_cast<float>(STATS_PV_MAX) * DIFF));
    this->manaBar_->setX2(X1 + (stats.get(Statistics::MANA_MAX) / static_cast<float>(STATS_MANA_MAX) * DIFF));
    this->powerBar_->setX2(X1 + (stats.get(Statistics::POWER) / static_cast<float>(STATS_POWER_MAX) * DIFF));
    this->defBar_->setX2(X1 + (stats.get(Statistics::DEFENSE) / static_cast<float>(STATS_DEF_MAX) * DIFF));
    this->critBar_->setX2(X1 + (stats.get(Statistics::CRITICAL) / static_cast<float>(STATS_CRIT_MAX) * DIFF));
    this->resiBar_->setX2(X1 + (stats.get(Statistics::RESILIENCE) / static_cast<float>(STATS_RESI_MAX) * DIFF));
    this->rangeBar_->setX2(X1 + (stats.get(Statistics::RANGE) / static_cast<float>(STATS_RANGE_MAX) * DIFF));
    this->speedBar_->setX2(X1 + (stats.get(Statistics::SPEED) / static_cast<float>(STATS_SPEED_MAX) * DIFF));
  }

  void	SelectPlayer::updateChampion()
  {
    this->updateTexts();
    this->updateStats();
    this->skillIcon_->setImage((*this->champion)->getSkillIcon());
    this->championImg_->setImage((*this->champion)->getAvatarFull());
  }

  void	SelectPlayer::nextPlayer()
  {
    Data *datas = Data::getInstance();
    Champion::Champion	*ref = (*this->champion);

    this->champion++;
    for (; this->champion != datas->championsPool.end(); ++this->champion)
      if (!(*this->champion)->isSelected())
	break;
    if (this->champion == datas->championsPool.end() || (*this->champion)->isSelected())
      for (this->champion = datas->championsPool.begin();
	   this->champion != datas->championsPool.end(); ++this->champion)
	if (!(*this->champion)->isSelected())
	  break;
    if (*this->champion != ref)
      this->updateChampion();
  }

  void	SelectPlayer::prevPlayer()
  {
    Data *datas = Data::getInstance();
    Champion::Champion	*ref = (*this->champion);

    if (this->champion == datas->championsPool.begin())
      this->champion = datas->championsPool.end();
    this->champion--;

    for (; this->champion != datas->championsPool.begin(); --this->champion)
      if (!(*this->champion)->isSelected())
	break;

    if ((*this->champion)->isSelected())
      for (this->champion = datas->championsPool.end();
	   this->champion != datas->championsPool.begin(); --this->champion)
	if (this->champion != datas->championsPool.end() && !(*this->champion)->isSelected())
	  break;

    if (*this->champion != ref)
      this->updateChampion();
  }

  void	SelectPlayer::placePlayer(Data *datas)
  {
    for (std::vector<Character::Player *>::iterator it = this->infos_->players.begin() ;
	 it != this->infos_->players.end() ; ++it)
      {
	if (*it)
	  {
	    (*it)->getNowState()->position.x = ((rand() % (datas->gameSettings.mapWidth / 2)
						 + 1) * 2) - 0.5;
	    (*it)->getNowState()->position.z = ((rand() % (datas->gameSettings.mapHeight / 2)
						 + 1) * 2) - 0.5;
	  }
      }
  }

  void	SelectPlayer::placeAI(Data *datas)
  {
    for (std::list<Character::AI *>::iterator it = this->infos_->AIs.begin() ;
	 it != this->infos_->AIs.end() ; ++it)
      {
	(*it)->getNowState()->position.x = ((rand() % (datas->gameSettings.mapWidth / 2)
					     + 1) * 2) - 0.5;
	(*it)->getNowState()->position.z = ((rand() % (datas->gameSettings.mapHeight / 2)
					     + 1) * 2) - 0.5;
      }
  }

  void	SelectPlayer::saveAndNext()
  {
    Data	*datas = Data::getInstance();
    int		i = static_cast<int>(this->id_) - static_cast<int>(State::SELECTPLAYER1);

    if (this->infos_->players[i])
      this->infos_->players[i]->setChampion((*this->champion));
    (*this->champion)->setSelected(true);

    if (static_cast<int>(this->id_) - static_cast<int>(State::SELECTPLAYER1) + 1
	< datas->gameSettings.nbrPlayers)
      datas->states->push(static_cast<State::e_State>(static_cast<int>(this->id_) + 1));
    else
      {
	if (this->infos_->map)
	  delete this->infos_->map;
	std::string AIName[15] = {"Wojcik", "Zamorski", "Sokolowski",
				  "Nazwisko", "Razowski", "Kowalski",
				  "Nowakski", "Wisniewski", "Zelenski",
				  "Rydzski", "Smiglyski", "Komorowski",
				  "Ujazdowski", "Cmielowski", "Andrychowski"};
	if  (datas->gameSettings.nbrAI == 0 && datas->gameSettings.nbrPlayers == 1)
	  datas->gameSettings.nbrAI = 1;
	for (int i = 0 ; i < datas->gameSettings.nbrAI; i++)
	  {
	    Character::AI *toAdd = new Character::AI(*this->infos_);
	    toAdd->setChampion(new Champion::Minion);
	    toAdd->getProfile().name = AIName[i];
	    this->infos_->AIs.push_back(toAdd);
	  }
	this->placePlayer(datas);
	this->placeAI(datas);
	this->infos_->map = new Map::GameMap(datas->gameSettings.mapWidth + 1,
					     datas->gameSettings.mapHeight + 1);
	this->infos_->map->generate(*this->infos_);
	datas->states->push(State::ARCADE);
      }
  }

  std::string	SelectPlayer::formatSkillText(std::string &str)
  {
    std::string		ret;
    std::string		tmp;
    unsigned int	max = 30;
    unsigned int	len = 0;

    std::istringstream	iss(str);
    while (iss >> tmp)
      {
	if (len + tmp.length() < max)
	  {
	    if (ret.length())
	      ret += " ";
	    ret += tmp;
	    len += tmp.length() + 1;
	  }
	else
	  {
	    ret += "\n" + tmp;
	    len = tmp.length();
	  }
	size_t pos = ret.find("\\n");
	while (pos != std::string::npos)
	  {
	    ret.replace(pos, 2, "\n");
	    len = ret.substr(pos).length();
	    pos = ret.find("\\n");
	  }
      }
    return (ret);
  }

  void	SelectPlayer::goBack()
  {
    int	i = static_cast<int>(this->id_) - static_cast<int>(State::SELECTPLAYER1);

    if (*this->champion)
      (*this->champion)->setSelected(false);
    if (this->infos_->players[i])
      this->infos_->players[i]->setChampion(0);
    Data::getInstance()->states->pop();
  }

  void	SelectPlayer::update()
  {
    if ((*this->champion)->isSelected())
      this->nextPlayer();
    while (!(this->events_->mouseEmpty()))
      {
    	std::list<AButton *>::iterator it;
    	Input::s_mouseEvent mouse = this->events_->popMouse();

    	if ((it = this->findButtons(mouse.pos.first,mouse.pos.second)) != this->buttons_.end())
    	  {
    	    if (mouse.clic == gdl::Mouse::Left)
    	      {
    		if (mouse.mouseState == Input::RELEASE)
    		  {
		    (this->*(this->funPtr)[(*it)->getId()])();
		  }
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

  void	SelectPlayer::initSelectPlayer()
  {
    Data *datas = Data::getInstance();
    unsigned int	textSize = 12;

    for (this->champion = datas->championsPool.begin();
    	 this->champion != datas->championsPool.end(); ++this->champion)
      if (!(*this->champion)->isSelected())
    	break;

    if (this->champion == datas->championsPool.end())
      this->champion = datas->championsPool.begin();

    Statistics	const &stats = (*this->champion)->getStats();

    this->imgPos_.setPos(550, 226, 794, 628);
    this->championImg_ = new Graphic::GuiImage(this->imgPos_,
    					       (*this->champion)->getAvatarFull());
    this->imgPos_.setPos(X1, 462, X1 + (stats.get(Statistics::HP_MAX) / static_cast<float>(STATS_PV_MAX) * DIFF), 476);
    this->hpBar_ =  new Graphic::GuiImage(this->imgPos_, &datas->imgs[Data::HP_BAR]);
    this->imgPos_.setPos(X1, 479, X1 + (stats.get(Statistics::MANA_MAX) / static_cast<float>(STATS_MANA_MAX) * DIFF), 492);
    this->manaBar_ =  new Graphic::GuiImage(this->imgPos_, &datas->imgs[Data::MANA_BAR]);
    this->imgPos_.setPos(X1, 495, X1 + (stats.get(Statistics::POWER) / static_cast<float>(STATS_POWER_MAX) * DIFF), 510);
    this->powerBar_ =  new Graphic::GuiImage(this->imgPos_, &datas->imgs[Data::POWER_BAR]);
    this->imgPos_.setPos(X1, 513, X1 + (stats.get(Statistics::DEFENSE) / static_cast<float>(STATS_DEF_MAX) * DIFF), 527);
    this->defBar_ =  new Graphic::GuiImage(this->imgPos_, &datas->imgs[Data::DEF_BAR]);
    this->imgPos_.setPos(X1, 530, X1 + (stats.get(Statistics::CRITICAL) / static_cast<float>(STATS_CRIT_MAX) * DIFF), 544);
    this->critBar_ =  new Graphic::GuiImage(this->imgPos_, &datas->imgs[Data::CRIT_BAR]);
    this->imgPos_.setPos(X1, 546, X1 + (stats.get(Statistics::RESILIENCE) / static_cast<float>(STATS_RESI_MAX) * DIFF), 561);
    this->resiBar_ =  new Graphic::GuiImage(this->imgPos_, &datas->imgs[Data::RESI_BAR]);
    this->imgPos_.setPos(X1, 564, X1 + (stats.get(Statistics::RANGE) / static_cast<float>(STATS_RANGE_MAX) * DIFF), 577);
    this->rangeBar_ =  new Graphic::GuiImage(this->imgPos_, &datas->imgs[Data::RANGE_BAR]);
    this->imgPos_.setPos(X1, 580, X1 + (stats.get(Statistics::SPEED) / static_cast<float>(STATS_SPEED_MAX) * DIFF), 594);
    this->speedBar_ =  new Graphic::GuiImage(this->imgPos_, &datas->imgs[Data::SPEED_BAR]);
    this->imgPos_.setPos(583, 186, 761, 217);
    this->profileBackground_ = new Graphic::GuiImage(this->imgPos_, &datas->imgs[Data::PROFILE_NAME_BACK]);

    this->initTextFromString(this->skill_, "", 906, 465, textSize);

    this->updateChampion();
  }

  void	SelectPlayer::reload()
  {
    int		i = static_cast<int>(this->id_) - static_cast<int>(State::SELECTPLAYER1);

    if (this->infos_->players[i])
      this->infos_->players[i]->setChampion(0);
    (*this->champion)->setSelected(false);
    this->updateChampion();
  }

  void	SelectPlayer::reset()
  {
    Data	*datas	= Data::getInstance();

    if (!this->init_)
      this->initSelectPlayer();

    bool	last = static_cast<int>(this->id_) - static_cast<int>(State::SELECTPLAYER1) + 1 == datas->gameSettings.nbrPlayers ? true : false;

    this->next_->setTextValue(datas->db.getText(datas->gameSettings.language, last ? "button_play" : "next"));
  }
}
