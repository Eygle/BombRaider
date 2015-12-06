#include <unistd.h>

#include "Menu/Binding/KeyButton.hpp"

namespace Menu
{
  KeyButton::KeyButton(std::vector<KeyButton *> &other, Input::EventManager *event,
		       std::map<Input::Key, std::string> &map, int player, int action,
		       int x1, int y1, int x2, int y2)
    : map_(map), other_(other), events_(event), player_(player), action_(action)
  {
    this->initAffichage(Data::BG_KEYS, Data::BG_KEYS_OVER, Data::BG_KEYS_CLICKED, this->position_);
    this->datas_ = Data::getInstance();
    //this->position_.setPos(x1, y1, x2, y2);
    this->setTextSize(12);
    this->setTextValue("");
    this->setPosition(x1, y1, x2, y2);
    int	key = this->datas_->db.getKey(player, action);
    if (key >= Input::A && key <= Input::Count)
      {
	this->setTextValue(this->map_[static_cast<Input::Key>(key)]);
	this->key_ = key;
      }
    this->centerText();
  }

  KeyButton::~KeyButton()
  {
  }

  int	KeyButton::getKey() const
  {
    return this->key_;
  }

  void	KeyButton::deleteKey()
  {
    this->key_ = -1;
    this->datas_->db.setKey(this->player_, this->action_, this->key_);
    this->setTextValue("");
  }

  void	KeyButton::deleteOtherKeys()
  {
    std::vector<KeyButton *>::iterator	it;

    for (it = this->other_.begin(); it != this->other_.end(); ++it)
      {
	if (*it != this && (*it)->getKey() == this->key_)
	  (*it)->deleteKey();
      }
  }

  void	KeyButton::action(char val)
  {
    Input::Key	key = static_cast<Input::Key>(val);

    if (this->map_.find(key) != this->map_.end())
      {
	this->setTextValue(this->map_[key]);
	this->centerText();
	this->key_ = val;
	this->datas_->db.setKey(this->player_, this->action_, this->key_);
	this->deleteOtherKeys();
      }
  }

  void	KeyButton::update()
  {
  }
}
