#ifndef __INPUTFIELD__
#define __INPUTFIELD__

#include <string>

#include "AButton.hpp"

namespace Menu
{
  class InputField
  {
  private:
    std::string	value_;
    int		limite_;
    int		size_;
  public :
    InputField(int limite = -1);
    virtual ~InputField();
  
    virtual void action(char c);
    virtual void update();
    virtual void draw();
  };
};
#endif
