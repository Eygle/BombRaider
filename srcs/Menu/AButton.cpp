
#include "Menu/AButton.hpp"

namespace Menu
{

  // CTOR
  AButton::AButton(int id)
    : isPressed_(false), focus_(false), isSelectedDurable_(false), value_(""), position_(0.0, 0.0, 0.0, 0.0),
      normal_(position_), hover_(position_), pressed_(position_),
      textSize_(12), id_(id)
  {
    this->isHover_ =  false;
    this->setTextSize(textSize_);
  }
  // DTOR
  AButton::~AButton()
  {}

  // GETTER
  const Graphic::ImagePosition	&AButton::getPosition() const
  {
    return (this->position_);
  }

  bool				AButton::getPressed() const
  {
    return (this->isPressed_);
  }

  // SETTER
  // Text
  void	AButton::setTextValue(const std::string &text)
  {
    this->value_ = text;
    this->text_.setText(text);
  }

  void	AButton::setTextPosition(int x, int y)
  {
    this->text_.setPosition(x, y);
  }

  bool	AButton::setTextFont(std::string const & fontPath)
  {
    return (this->text_.setFont(fontPath));
  }

  void	AButton::setTextColor(gdl::Color const & color)
  {
    this->text_.setColor(color);
  }

  void	AButton::setTextSize(unsigned int size)
  {
    this->textSize_ = size;
    this->text_.setSize(size);
  }

  void	AButton::setSelected(bool sel)
  {
    this->isSelectedDurable_ = sel;
  }


  // Image
  void	AButton::setNormal(Graphic::GuiImage &normal)
  {
    this->normal_ = normal;
  }

  void	AButton::setHover(Graphic::GuiImage &hover)
  {
    this->hover_ = hover;
  }

  void	AButton::setFocus(bool focus)
  {
    this->focus_ = focus;
  }

  // Position
  void	AButton::setPosition(Graphic::ImagePosition const &pos)
  {
    this->position_ = pos;
    this->setTextPosition(this->position_.x1_, this->position_.y1_);
    this->hover_.setImagePosition(pos);
    this->normal_.setImagePosition(pos);
    this->pressed_.setImagePosition(pos);
  }

  void	AButton::setPosition(int x1, int y1, int x2, int y2)
  {
    Graphic::ImagePosition pos(x1, y1, x2, y2);
    this->setPosition(pos);
  }

  // GETTER
  const std::string &AButton::getText()
  {
    return (this->value_);
  }

  // METHODE

  void	AButton::draw()
  {
    if (this->isPressed_ || this->isSelectedDurable_)
      this->pressed_.draw();
    else if (this->isHover_ || this->focus_)
      this->hover_.draw();
    else
      this->normal_.draw();
    this->text_.draw();
    this->isHover_ = false;
    this->isPressed_ = false;
  }

  // MEMBER FUNCTION

  bool	AButton::isIn(float x, float y) const
  {
    if (this->position_.x1_ < x && this->position_.x2_ > x && this->position_.y1_ < y && this->position_.y2_ > y)
      return (true);
    return (false);
  }

  void	AButton::centerText()
  {
    int	width = this->position_.x2_ - this->position_.x1_;
    int	height = this->position_.y2_ - this->position_.y1_;
    int lenght = (this->value_.size() / 2) * this->textSize_;
    width = (width - lenght) / 2;
    height = (height - this->textSize_)  / 2;
    this->setTextPosition(this->position_.x1_ + width,this->position_.y1_ + height);
  }

  void	AButton::initAffichage(Data::e_image normal, Data::e_image hover,
			       Data::e_image pressed, Graphic::ImagePosition const &pos)
  {
    Data	*data = Data::getInstance();

    Graphic::GuiImage		inormal(pos, &(data->imgs[normal]));
    Graphic::GuiImage		ihover(pos, &(data->imgs[hover]));
    Graphic::GuiImage		ipressed(pos, &(data->imgs[pressed]));
    this->normal_ = inormal;
    this->hover_ = ihover;
    this->pressed_ = ipressed;
  }

  void	AButton::activateHover()
  {
    this->isHover_ = true;
  }
  void	AButton::activatePress()
  {
    this->isPressed_ = true;
  }

  int	AButton::getId() const
  {
    return this->id_;
  }

  void	AButton::desactivatePress()
  {
    this->isPressed_ = false;
  }
}
