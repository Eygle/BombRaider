#ifndef __BUFF_HPP__
#define __BUFF_HPP__

# include "Map/AEntity.hpp"
# include "Statistics.hpp"
# include "GDL/IClock.hpp"
# include "Map/EItems.hpp"

namespace Map
{
  class Buff : public AEntity
  {
    Statistics	_stats;

    Buff(Buff const &);
    Buff& operator=(Buff const &);

  public:
    Buff(Map::e_item, Statistics const &, int, int);
    ~Buff();

    bool action(Character::Character *);
    bool takeDmg(Statistics const &);

    void	save(TiXmlElement *, GameInfo *);

    virtual void	update();
  };
};

#endif
