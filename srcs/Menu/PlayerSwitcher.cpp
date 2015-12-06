#include "Menu/PlayerSwitcher.hpp"

namespace Menu
{
  PlayerSwitcher::PlayerSwitcher(int x1, int y1, int x2 , int y2)
  {
    std::stringstream	tmp;
    std::string		tmp2;
    this->max_ = 4;
    this->min_ = 1;
    Graphic::ImagePosition bposition(x1, y1, x2, y2);
    Graphic::ImagePosition biposition(x1, y1, x2+20, y2);
    Graphic::ImagePosition cposition(x1, y1, x1+20, y2);
    this->bposition_ = bposition;
    this->cposition_ = cposition;
    this->normal_.setImagePosition(biposition);
    this->cursor_.setImagePosition(this->cposition_);
    this->value_ = this->data_->gameSettings.nbrPlayers;
    this->updateFromValue();
    this->pvalue_ = this->data_->db.getText(this->data_->gameSettings.language, "player");
    tmp << this->value_;
    tmp >> tmp2;
    this->svalue_  = this->pvalue_;
    this->svalue_ += " : ";
    this->svalue_ += tmp2;
    this->setTextValue(this->svalue_);
    this->setTextSize(18);
    this->setTextPosition(351,y1);
  }
  
  PlayerSwitcher::~PlayerSwitcher()
  {
  }
    
  void	PlayerSwitcher::update()
  {
    this->data_->gameSettings.nbrPlayers = this->value_;
  }
  
  void	PlayerSwitcher::action(char )
  {
  }

  unsigned int	*PlayerSwitcher::getNbPlayer()
  {
    return (&(this->value_));
  }

}
