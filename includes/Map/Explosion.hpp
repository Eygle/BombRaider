#ifndef __EXPLOSION_HPP__
# define __EXPLOSION_HPP__

# include <utility>

# include "Map/AEntity.hpp"
# include "GDL/Clock.hpp"

namespace Character
{
  class Character;
}

namespace Map
{
  class Explosion : public AEntity
  {
    Character::Character	*_origin;
    Statistics			_stats;
    gdl::Clock			_duration;
    std::pair<int, int>		_coord;

    Explosion(Explosion const &);
    Explosion& operator=(Explosion const &);

  public:
    Explosion(Character::Character *, Statistics const &, int, int);
    ~Explosion();

    bool action(Character::Character *);
    bool takeDmg(Statistics const &);
    bool isExtinct();

    std::pair<int, int>	&getCoord();
    Statistics const	&getStats();
  };
};

#endif
