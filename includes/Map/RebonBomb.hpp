#ifndef __REBON_BOMB_HPP__
#define __REBON_BOMB_HPP__

# include "Map/ABomb.hpp"
# include "Clock/Clock.hpp"

namespace Map
{
  class RebonBomb : public ABomb
  {
    Clock	*_globalClock;
    bool	_isAscending;
    void	explode();
    bool	move();
    void	init(float);

    RebonBomb(RebonBomb const &);
    RebonBomb& operator=(RebonBomb const &);

  public:
    RebonBomb(Character::Character *, Clock *);
    RebonBomb(Character::Character *, Clock *, float);
    void	update();
    ~RebonBomb();

    bool	action(Character::Character *);
  };
};

#endif
