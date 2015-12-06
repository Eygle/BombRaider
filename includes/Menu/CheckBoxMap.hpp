#ifndef __CHECKBOXMAP__
#define __CHECKBOXMAP__

#include "Data.hpp"
#include "AButton.hpp"

namespace Menu
{
  class CheckBoxMap : public AButton 
  {
    bool			checked_;
    Data			*data_;
  public:
    CheckBoxMap();
    ~CheckBoxMap();
    virtual	void action(char c);
    virtual	void update();
    virtual	void draw();
  };
  
};

#endif
