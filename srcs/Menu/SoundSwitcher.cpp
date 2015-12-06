#include "Menu/SoundSwitcher.hpp"

namespace Menu
{
  SoundSwitcher::SoundSwitcher(Sound::e_soundType type)
    : value_(100),  type_(type), cposition_(0, 0, 0, 0), bposition_(0, 0, 0, 0), cursor_(cposition_,0), data_(Data::getInstance())
  {
    Graphic::ImagePosition pos(0,0,0,0);
    Graphic::GuiImage		inormal(pos, &(this->data_->imgs[Data::BARRE]));
    Graphic::GuiImage		ihover(pos, &(this->data_->imgs[Data::CURSOR]));

    this->normal_ = inormal;
    this->cursor_ = ihover;
  }

  SoundSwitcher::~SoundSwitcher()
  {
  }

  void	SoundSwitcher::update()
  {
    this->data_->soundManager->changeVol(this->type_, this->value_);
    if (this->getText() == this->data_->db.getText(this->data_->gameSettings.language, "music")){
      this->data_->db.setMusicVol(this->value_);
    }
    else if (this->getText() == this->data_->db.getText(this->data_->gameSettings.language, "noises")){
      this->data_->db.setNoisesVol(this->value_);
    }
    else{
      this->data_->db.setVoicesVol(this->value_);
    }
  }

  void	SoundSwitcher::action(char)
  {
  }

  void	SoundSwitcher::draw()
  {
    this->text_.draw();
    this->normal_.draw();
    this->cursor_.draw();
  }

  void		SoundSwitcher::setValue(int y)
  {
    int tmp = y - this->bposition_.x1_;
    if (tmp < 0)
      this->value_ = 0;
    else
      this->value_ = (tmp * 100) / (this->bposition_.x2_ - this->bposition_.x1_);
    if (this->value_ > 100)
      this->value_ = 100;
    this->updateCursor();
  }

  void		SoundSwitcher::setValueDir(int value)
  {
    this->value_ = value;
  }

  void		SoundSwitcher::setCursorPosition(int x1, int y1, int x2, int y2)
  {
    Graphic::ImagePosition pos(x1,y1,x2,y2);
    this->cposition_ = pos;
    this->cursor_.setImagePosition(pos);
  }

  void		SoundSwitcher::setCursor(const Graphic::GuiImage &cursor)
  {
    this->cursor_ = cursor;
  }

  void		SoundSwitcher::updateCursor()
  {
    this->cposition_.x1_ = this->bposition_.x1_ + (this->bposition_.x2_ - this->bposition_.x1_) / 100 * this->value_;
    this->cposition_.x2_ = this->cposition_.x1_ + 10 ;
    this->cursor_.setImagePosition(this->cposition_);
  }

  void		SoundSwitcher::setBarrePosition(int x1, int y1, int x2, int y2)
  {
    Graphic::ImagePosition pos(x1,y1,x2,y2);
    Graphic::ImagePosition posi(x1,y1,x2+12,y2);
    this->bposition_ = pos;
    this->normal_.setImagePosition(posi);
  }

  bool		SoundSwitcher::isSelected(int x, int y)
  {
    if (x >= this->bposition_.x1_ && this->bposition_.x2_ >= x)
      {
	if (y >= this->bposition_.y1_ && this->bposition_.y2_ >= y)
	  return (true);
      }
    return (false);
  }

  std::list<SoundSwitcher *> initSoundSwitcher(void)
  {
    std::list<SoundSwitcher *> result;
    Data	*data = Data::getInstance();

    SoundSwitcher *music = new SoundSwitcher(Sound::AMBIANCE);
    music->setTextValue(data->db.getText(data->gameSettings.language, "music"));
    music->setTextSize(18);
    music->setTextPosition(399,277);
    music->setBarrePosition(531, 277, 934, 299);
    music->setCursorPosition(934, 277, 946, 299);
    music->setValueDir(data->db.getMusicVol());
    music->updateFromValue();

    SoundSwitcher *noise = new SoundSwitcher(Sound::NOISE);
    noise->setTextValue(data->db.getText(data->gameSettings.language, "noises"));
    noise->setTextPosition(399,327);
    noise->setTextSize(18);
    noise->setBarrePosition(531, 327, 934, 349);
    noise->setCursorPosition(934, 327, 946, 349);
    noise->setValueDir(data->db.getNoisesVol());
    noise->updateFromValue();

    SoundSwitcher *voice = new SoundSwitcher(Sound::VOICE);
    voice->setTextValue(data->db.getText(data->gameSettings.language, "voices"));
    voice->setTextPosition(399,377);
    voice->setTextSize(18);
    voice->setBarrePosition(531, 377, 934, 399);
    voice->setCursorPosition(934, 377, 946, 399);
    voice->setValueDir(data->db.getVoicesVol());
    voice->updateFromValue();

    result.push_back(music);
    result.push_back(noise);
    result.push_back(voice);
    return (result);
  }

  void	SoundSwitcher::updateFromValue()
  {
    double	intervale = 100;
    double	sizeInterval = this->bposition_.x2_ - this->bposition_.x1_;

    double	csize = this->cposition_.x2_ - this->cposition_.x1_;

    this->cposition_.x1_ = ((this->value_) / intervale) * sizeInterval + this->bposition_.x1_;
    this->cposition_.x2_ = this->cposition_.x1_ + csize;
    this->cursor_.setImagePosition(this->cposition_);
  }
}
