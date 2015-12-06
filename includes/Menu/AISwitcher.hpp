#ifndef __AISWITCHER__
#define __AISWITCHER__

#include "Switcher.hpp"

namespace Menu
{
  class AISwitcher  : public Switcher
  {
  public :
    AISwitcher(int x1, int x2, int y1, int y2);
    ~AISwitcher();
    
    virtual	void update();
    virtual	void action(char c);
  };
};

#endif
