#ifndef __FUFU_BOMB_HPP__
#define __FUFU_BOMB_HPP__

# include "Map/ABomb.hpp"

namespace Map
{
  class FufuBomb : public ABomb
  {
    FufuBomb(FufuBomb const &);
    FufuBomb& operator=(FufuBomb const &);

    void	explode();

  public:
    FufuBomb(Character::Character *);
    FufuBomb(int, int, GameMap &, std::list<Explosion *> &,
		std::list<ABomb *> &, Statistics const &);
    ~FufuBomb();
  };
};

#endif
