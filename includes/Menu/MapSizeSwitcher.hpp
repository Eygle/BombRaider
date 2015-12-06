#ifndef __MAPSWITCHER__
#define __MAPSWITCHER__

#include "Switcher.hpp"

namespace Menu
{
  class MapSizeSwitcher  : public Switcher
  {
  public :
    MapSizeSwitcher(int x1, int x2, int y1, int y2);
    ~MapSizeSwitcher();
    
    virtual	void update();
    virtual	void action(char c);
  };
};

#endif
