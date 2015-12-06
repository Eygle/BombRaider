#ifndef __BOX_HPP__
# define __BOX_HPP__

# include "Map/AEntity.hpp"
# include "Map/EItems.hpp"
# include "GDL/Clock.hpp"
# include "GameInfo.hpp"
# include "XML/ticpp.h"

namespace Character
{
  class Character;
};

namespace Map
{
  class Box : public AEntity
  {
    Statistics	_stats;
    gdl::Clock	_invulnerability;

    Box(Box const &);
    Box& operator=(Box const &);

  public:
    Box(Map::e_item, Statistics const &, int, int);
    ~Box();

    bool action(Character::Character *);
    bool takeDmg(Statistics const &);

    void	save(TiXmlElement *, GameInfo *);
  };
};

#endif
