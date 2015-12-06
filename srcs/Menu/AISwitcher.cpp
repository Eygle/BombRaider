#include "Menu/AISwitcher.hpp"

namespace Menu
{
  AISwitcher::AISwitcher(int x1, int y1, int x2 , int y2)
  {
    std::stringstream	tmp;
    std::string		tmp2;

    this->max_ = 15;
    this->min_ = 0;
    Graphic::ImagePosition bposition(x1, y1, x2, y2);
    Graphic::ImagePosition biposition(x1, y1, x2+20, y2);
    Graphic::ImagePosition cposition(x1, y1, x1+20, y2);
    this->bposition_ = bposition;
    this->cposition_ = cposition;
    this->normal_.setImagePosition(biposition);
    this->cursor_.setImagePosition(this->cposition_);
    this->value_ = this->data_->gameSettings.nbrAI;
    this->updateFromValue();
    this->pvalue_ = this->data_->db.getText(this->data_->gameSettings.language, "ai");
    tmp << this->value_;
    tmp >> tmp2;
    this->svalue_  = this->pvalue_;
    this->svalue_ += " : ";
    this->svalue_ += tmp2;
    this->setTextValue(this->svalue_);
    this->setTextSize(18);
    this->setTextPosition(x1-60,y1);
  }
  
  AISwitcher::~AISwitcher()
  {
  }
    
  void	AISwitcher::update()
  {
    this->data_->gameSettings.nbrAI = this->value_;
  }
  
  void	AISwitcher::action(char )
  {
  }

}
