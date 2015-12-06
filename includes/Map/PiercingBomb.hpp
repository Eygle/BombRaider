#ifndef __PIERCING_BOMB_HPP__
# define __PIERCING_BOMB_HPP__

# include "Map/ABomb.hpp"

namespace Map
{
  class PiercingBomb : public ABomb
  {
    PiercingBomb(PiercingBomb const &);
    PiercingBomb& operator=(PiercingBomb const &);

    bool	addExplosion(int, int);
    void	explode();

  public:
    PiercingBomb(Character::Character *);
    ~PiercingBomb();
  };
};

#endif
