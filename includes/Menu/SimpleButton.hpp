#ifndef __SIMPLEBUTTON__
#define __SIMPLEBUTTON__

#include "AButton.hpp"

namespace Menu
{
  class SimpleButton : public AButton
  {
  public:
    SimpleButton();
    virtual ~SimpleButton();
    
    virtual void	action( char c = 0);
    virtual void	draw();
    virtual void	update();
  };
};

#endif
