#include "Menu/Switcher.hpp"

namespace Menu
{
  Switcher::Switcher()
    : max_(100), min_(0), value_(0), cposition_(0), bposition_(0), cursor_(0), data_(Data::getInstance())
    , svalue_(""), pvalue_("")
  {
    Graphic::ImagePosition pos(0,0,0,0);
    Graphic::GuiImage		inormal(pos, &(this->data_->imgs[Data::BARRE]));
    Graphic::GuiImage		ihover(pos, &(this->data_->imgs[Data::CURSOR]));

    this->normal_ = inormal;
    this->cursor_ = ihover;
  }

  Switcher::~Switcher()
  {
  }

  void	Switcher::update()
  {
  }

  void	Switcher::action(char)
  {

  }

  void	Switcher::draw()
  {
    this->text_.draw();
    this->normal_.draw();
    this->cursor_.draw();
  }

  bool	Switcher::isSelected(int x, int y)
  {
    if (this->cposition_.x1_ <= x && this->cposition_.x2_ >= x
	&& this->cposition_.y1_ <= y && this->cposition_.y2_ >= y)
      return (true);
    return (false);
  }

  void	Switcher::modifieValue(int y)
  {
	double	intervale = this->max_ - this->min_;
	double	sizeInterval = this->bposition_.x2_ - this->bposition_.x1_;
	double	position_in = y - this->bposition_.x1_;
	double	csize = this->cposition_.x2_ - this->cposition_.x1_;
	double	ratio = position_in / sizeInterval;
	if (y >= this->bposition_.x2_)
	  this->value_ = this->max_;
	else if (y <= this->bposition_.x1_)
	  this->value_ = this->min_;
	else
	  this->value_ = (ratio * intervale) + this->min_;
	this->cposition_.x1_ = ((this->value_ - this->min_) / intervale) * sizeInterval + this->bposition_.x1_;
	this->cposition_.x2_ = this->cposition_.x1_ + csize;
	this->cursor_.setImagePosition(this->cposition_);
	std::stringstream	tmp;
	std::string		tmp2;

	this->data_->gameSettings.mapHeight = this->value_* 2;
	this->data_->gameSettings.mapWidth = this->value_ * 2;
	tmp << " " << this->value_;
	tmp >> tmp2;
	this->svalue_ = this->pvalue_;
	this->svalue_ += " : ";
	this->svalue_ += tmp2;
	this->setTextValue(this->svalue_);
  }

  void	Switcher::updateFromValue()
  {
    double	intervale = this->max_ - this->min_;
    double	sizeInterval = this->bposition_.x2_ - this->bposition_.x1_;
    double	csize = this->cposition_.x2_ - this->cposition_.x1_;

    this->cposition_.x1_ = ((this->value_ - this->min_) / intervale) * sizeInterval + this->bposition_.x1_;
    this->cposition_.x2_ = this->cposition_.x1_ + csize;
    this->cursor_.setImagePosition(this->cposition_);
  }
}
