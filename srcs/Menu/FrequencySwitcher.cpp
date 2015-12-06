#include "Menu/FrequencySwitcher.hpp"

namespace Menu
{
  FrequencySwitcher::FrequencySwitcher(int x1, int y1, int x2 , int y2, bool bonus):
    bonus_(bonus)
  {
    this->max_ = 100;
    this->min_ = 0;
    Graphic::ImagePosition bposition(x1, y1, x2, y2);
    Graphic::ImagePosition biposition(x1, y1, x2+20, y2);
    Graphic::ImagePosition cposition(x1, y1, x1+20, y2);
    this->bposition_ = bposition;
    this->cposition_ = cposition;
    this->normal_.setImagePosition(biposition);
    this->cursor_.setImagePosition(this->cposition_);
    if (this->bonus_)
      {
	this->pvalue_ = this->data_->db.getText(this->data_->gameSettings.language, "bonus_freq");
	this->value_ = this->data_->gameSettings.bonusFrequency;
      }
    else 
      {
	this->pvalue_ = this->data_->db.getText(this->data_->gameSettings.language, "box_freq");
	this->value_ = this->data_->gameSettings.boxFrequency;
      }
    this->updateFromValue();
    std::stringstream	tmp;
    std::string		tmp2;
    tmp << this->value_;
    tmp >> tmp2;
    this->svalue_  = this->pvalue_;
    this->svalue_ += " : ";
    this->svalue_ += tmp2;
    this->setTextValue(this->svalue_);
    this->setTextSize(18);
    this->setTextPosition(x1-200,y1);
  }
  
  FrequencySwitcher::~FrequencySwitcher()
  {
  }
    
  void	FrequencySwitcher::update()
  {
    if (this->bonus_)
      this->data_->gameSettings.bonusFrequency = this->value_;
    else 
      this->data_->gameSettings.boxFrequency = this->value_;
  }
  
  void	FrequencySwitcher::action(char )
  {
  }

}
