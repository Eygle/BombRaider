#ifndef __PLAYERSWITCHER__
#define __PLAYERSWITCHER__

#include "Switcher.hpp"

namespace Menu
{
  class PlayerSwitcher  : public Switcher
  {
  public :
    PlayerSwitcher(int x1, int x2, int y1, int y2);
    ~PlayerSwitcher();
    
    virtual void	update();
    virtual void	action(char c);
    unsigned int	*getNbPlayer();
  };
};

#endif
