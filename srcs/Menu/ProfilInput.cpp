#include "Profile.hpp"
#include "Character/Player.hpp"
#include "Menu/ProfilInput.hpp"

namespace Menu
{
  ProfilInput::ProfilInput(int id)
    : svalue_("") , maxSize_(16) , curSize_(0), id_(id)
  {
    this->tvalue_.setText(this->svalue_);
    this->isPressed_ = false;
    this->isHover_ = false;
    this->isSelectedDurable_ = false;
  }
  ProfilInput::~ProfilInput()
  {
  }

  void	ProfilInput::action(char c)
  {
    if (c == '\b')
      {
	if (this->curSize_ > 0)
	  {
	    this->curSize_ -= 1;
	    this->svalue_.erase(this->curSize_, 1);
	    this->tvalue_.setText(this->svalue_);
	  }
      }
    else
      {
	if (this->curSize_  < this->maxSize_)
	  {
	    this->curSize_++;
	    this->svalue_ += c;
	    this->tvalue_.setText(this->svalue_);
	  }
      }
  }

  void	ProfilInput::init(GameInfo *info)
  {
    this->infos_ = info;
  }


  void	ProfilInput::update()
  {
    Data *data = Data::getInstance();

    if (this->svalue_ == "" )
      {
	std::stringstream	ss;

	ss << "Unamed";
	ss << this->id_+1;
	ss >> this->svalue_;
	this->tvalue_.setText(this->svalue_);
	this->curSize_ = this->svalue_.size();
      }
    Profile *profile = data->db.getProfile(this->svalue_);
    if (this->infos_->players[this->id_])
      {
	delete this->infos_->players[this->id_];
	this->infos_->players[this->id_] = 0;
      }
    this->infos_->players[this->id_] = new Character::Player(*this->infos_, this->id_);
    this->infos_->players[this->id_]->setTrueProfile(profile);
  }

  void	ProfilInput::draw()
  {
    if (this->isPressed_ || this->isSelectedDurable_)
      this->pressed_.draw();
    else if (this->isHover_ || this->focus_)
      this->hover_.draw();
    else
      this->normal_.draw();
    this->tvalue_.draw();
    this->text_.draw();
  }

  void  ProfilInput::initInput(std::string const &text, int y1)
  {
    Graphic::ImagePosition	pos(560,y1,720,y1+20);

    this->setPosition(pos);
    this->initAffichage(Data::BG_KEYS, Data::BG_KEYS_OVER, Data::BG_KEYS_CLICKED, pos);
    this->setTextValue(text);
    this->setTextPosition(470,y1+1);
    this->setTextSize(18);
    this->tvalue_.setSize(10);
    this->tvalue_.setPosition(570, y1+5);
  }
}
