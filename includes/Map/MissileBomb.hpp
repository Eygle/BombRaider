#ifndef __MISSILE_BOMB_HPP__
# define __MISSILE_BOMB_HPP__

# include "Map/ABomb.hpp"
# include "Clock/Clock.hpp"

namespace Map
{
  class MissileBomb : public ABomb
  {
    Clock	*_globalClock;

    void	explode();
    bool	move();
    void	init(float);

    MissileBomb(MissileBomb const &);
    MissileBomb& operator=(MissileBomb const &);

  public:
    MissileBomb(Character::Character *, Clock *);
    MissileBomb(Character::Character *, Clock *, float);
    ~MissileBomb();

    bool	action(Character::Character *);
  };
};

#endif
