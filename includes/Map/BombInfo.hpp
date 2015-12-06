#ifndef __BOMB_INFO_HPP__
# define __BOMB_INFO_HPP__

# include "Map/EItems.hpp"
# include "Statistics.hpp"

namespace Map
{
  struct BombInfo
  {
    float	timeToExplode;
    e_item	type;
    int		x;
    int		y;
    Statistics	stats;
    int		manaConso;
    bool	isDroppable;

    BombInfo(float, e_item, int, int, Statistics const &, int, bool);
    BombInfo(BombInfo const &);
    BombInfo& operator=(BombInfo const &);
    ~BombInfo();

  private:
    BombInfo();
  };
};
#endif
