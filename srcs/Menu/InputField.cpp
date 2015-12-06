#include "Menu/InputField.hpp"

namespace Menu
{
  InputField::InputField(int limite) 
    : value_(""), limite_(limite), size_(0)
  {
  }
  
  InputField::~InputField()
  {
  }

  void InputField::action(char c)
  {
    if (c == '\b' && size > 0)
      {
	this->size_--;
      }
    else
      {
	if ((this->limit_ >  0 && this->size_ <= this->limit_) || this->limite < 0) 
	  {
	    this->value_ += c;
	    this->size++;
	  }
      }
  }

  void InputField::update()
  {
    this->setTextValue(this->value_);
  }
}
