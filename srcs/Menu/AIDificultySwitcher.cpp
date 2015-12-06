#include "Menu/AIDificultySwitcher.hpp"

namespace Menu
{
  AIDificultySwitcher::AIDificultySwitcher(int x1, int y1, int x2 , int y2)
  {
    this->max_ = 4;
    this->min_ = 1;
    Graphic::ImagePosition bposition(x1, y1, x2, y2);
    Graphic::ImagePosition biposition(x1, y1, x2+20, y2);
    Graphic::ImagePosition cposition(x1, y1, x1+20, y2);
    this->bposition_ = bposition;
    this->cposition_ = cposition;
    this->normal_.setImagePosition(biposition);
    this->cursor_.setImagePosition(this->cposition_);
    this->pvalue_ = this->data_->db.getText(this->data_->gameSettings.language, "difficulty");
    this->value_ = this->data_->gameSettings.difficulty;
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
  
  AIDificultySwitcher::~AIDificultySwitcher()
  {
  }
    
  void	AIDificultySwitcher::update()
  {
    this->data_->gameSettings.difficulty = this->value_;
  }
  
  void	AIDificultySwitcher::action(char )
  {
  }
}
