#include <map>
#include <algorithm>    // std::sort
#include "Menu/ScoreState.hpp"
#include "Menu/SwitchStateButton.hpp"
#include "Data.hpp"
#include "Character/Player.hpp"
#include "Character/AI.hpp"
#include "Database/IDatabase.hpp"


namespace Menu
{
  // SCORE PROFIL

  ScoreProfil::ScoreProfil(e_ranking rank, const std::string &name, Graphic::Image *avatar)
    : medal_(0), avatar_(0), name_(name)
  {
    std::map<e_ranking, Data::e_image> MEDALBIND;
    MEDALBIND[BRONZE] =  Data::MEDAL_BRONZE;
    MEDALBIND[SILVER] =  Data::MEDAL_SILVER;
    MEDALBIND[GOLD] =  Data::MEDAL_GOLD;
    MEDALBIND[PLATINE] =  Data::MEDAL_PLATINE;
    MEDALBIND[DIAMOND] =  Data::MEDAL_DIAMOND;
    MEDALBIND[CHALLENGER] =  Data::MEDAL_CHALLENGER;
    Data *data = Data::getInstance();
    int	y = rank * 40 + 270;
    Graphic::GuiImage imedal(pos_, &(data->imgs[MEDALBIND[rank]]));

    this->medal_ = imedal;
    Graphic::ImagePosition	pos(490,y,870,y+40);

    this->pos_ = pos;
    this->setMedalPos();
    this->setPosition(580, y+15,760, y+35);
    Graphic::ImagePosition	pos2(580,y+15,760,y+35);
    this->setTextValue(name);
    this->setTextSize(15);
    this->centerText();
    Graphic::GuiImage inormal(pos2,  &(data->imgs[Data::BG_KEYS]));
    this->setNormal(inormal);
    if (avatar)
      {
	Graphic::ImagePosition avapos(825,y,870,y+40);
	Graphic::GuiImage iavatar(avapos, avatar);
	this->avatar_ = iavatar;
      }
  }

  ScoreProfil::~ScoreProfil()
  {
  }

  void	ScoreProfil::draw()
  {
    this->medal_.draw();
    this->normal_.draw();
    this->avatar_.draw();
    this->text_.draw();
  }

  void	ScoreProfil::update()
  {
  }
  void	ScoreProfil::action(char)
  {
  }

  void ScoreProfil::setMedalPos()
  {
    Graphic::ImagePosition fpos(this->pos_.x1_, this->pos_.y1_,this->pos_.x1_+50,this->pos_.y1_+40);
    this->medal_.setImagePosition(fpos);
  }

  // SCORE STATE
  ScoreState::ScoreState(bool score) : init_(false), score_(score), layout_(0)
  {
    Data *data = Data::getInstance();
    SwitchStateButton *back = new SwitchStateButton(data->states, false, State::MAINMENU, true);
    Graphic::ImagePosition	layoutp(332,207,1023,648);
    back->initAffichage(Data::PREV_ARROW, Data::PREV_ARROW_OVER, Data::PREV_ARROW_CLICKED,layoutp);
    this->initButton(back, "", 368, 573, 434, 632 );
    this->setBackground(Data::BG_MENU);
    Graphic::ImagePosition	ptitle(545,220,810,245);
    Graphic::GuiImage		ititle(ptitle,  &(data->imgs[Data::BG_KEYS]));
    this->title_ = new SimpleButton();
    this->title_->setNormal(ititle);
    this->title_->setPosition(ptitle);
    this->title_->setTextValue(data->db.getText(data->gameSettings.language, "button_ranking"));
    this->title_->setTextSize(18);
    this->title_->centerText();
    Graphic::GuiImage		layout(layoutp,  &(data->imgs[Data::LAYOUT_PAUSE]));
    this->layout_ = layout;
  }

  ScoreState::~ScoreState()
  {
  }

  std::list<Character::Character *> ScoreState::getTop()
  {
    std::list<Character::Character *> result;

    std::vector<Character::Player *>::iterator it = this->infos_->players.begin();
    std::vector<Character::Player *>::iterator end = this->infos_->players.end();
    while (it != end)
      {
	if (*it)
	  {
	    Character::Character *tmp = *it;
	    result.push_back(tmp);
	  }
	it++;
      }
    result.insert(result.end(),this->infos_->AIs.begin(), this->infos_->AIs.end());
    result.sort(compareChar);
    return (result);
  }

  void	ScoreState::draw()
  {
    this->background_.draw();
    this->layout_.draw();
    this->drawProfile();
    this->drawButton();
    this->title_->draw();
}

  void	ScoreState::reset()
  {
    std::list<ScoreProfil  *>::iterator it = this->profils_.begin();
    std::list<ScoreProfil  *>::iterator end = this->profils_.end();
    
    while (it != end)
      {
	if (*it)
	 delete (*it);
	++it;
      }
    this->profils_.clear();
    if (this->score_)
      this->initScore();
    else
      this->initRanking();
    this->init_ = true;
  }

  void	ScoreState::update()
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

  void  ScoreState::initScore()
  {
    std::list<Character::Character *> top = this->getTop();
    std::list<Character::Character *>::iterator it = top.begin();
    std::list<Character::Character *>::iterator end = top.end();
    int	i = 0;
    while (it != end && i < 6)
      {
	ScoreProfil *tmp = new ScoreProfil(static_cast<e_ranking>(i), (*it)->getProfile().name,
					   (*it)->getChampion()->getAvatarSmall());
	this->profils_.push_back(tmp);
	++it;
	i++;
      }
  }

  void	ScoreState::initRanking()
  {
    Data *data = Data::getInstance();
    std::list<Database::Score *> score;
    data->db.getScores(score, 6, 1);
    std::list<Database::Score *>::iterator it = score.begin();
    std::list<Database::Score *>::iterator end = score.end();
    int	i = 0;
    while (it != end)
      {
	ScoreProfil *tmp = new ScoreProfil(static_cast<e_ranking>(i), (*it)->name, 0);
	this->profils_.push_back(tmp);
	++it;
	i++;
      }
  }

  void	ScoreState::drawProfile()
  {
    std::list<ScoreProfil  *>::iterator it = this->profils_.begin();
    std::list<ScoreProfil  *>::iterator end = this->profils_.end();

    while (it != end)
     {
       (*it)->draw();
       ++it;
     }
  }

  bool compareChar(Character::Character *c1, Character::Character *c2)
  {
    Profile  p1 = c1->getProfile();
    Profile  p2 = c2->getProfile();
     if (p2.score > p1.score)
      return (false);
    return (true);
  }


}
