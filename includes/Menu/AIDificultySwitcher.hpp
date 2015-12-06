#ifndef __AIDIFICULTYSWITCHER__
#define __AIDIFICULTYSWITCHER__

#include "Switcher.hpp"

namespace Menu
{
  class AIDificultySwitcher  : public Switcher
  {
  public :
    AIDificultySwitcher(int x1, int x2, int y1, int y2);
    ~AIDificultySwitcher();
    
    virtual void	update();
    virtual void	action(char c);
  };
};


#endif
