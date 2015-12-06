#ifndef __FREQUENCYSWITCHER__
#define __FREQUENCYSWITCHER__

#include "Switcher.hpp"

namespace Menu
{
  class FrequencySwitcher  : public Switcher
  {
    bool	bonus_;
 public :
    FrequencySwitcher(int x1, int x2, int y1, int y2, bool bonus);
    ~FrequencySwitcher();
    
    virtual	void update();
    virtual	void action(char c);
  };
};

#endif
