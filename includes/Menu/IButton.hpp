#ifndef __IBUTTON__
#define __IBUTTON__

namespace Menu
{
  class IButton 
  {
  public :
    virtual ~IButton(){};
    virtual void action(char c = 0) = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
  };
};
#endif
