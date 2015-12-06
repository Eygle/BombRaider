#ifndef __WALL_HPP__
# define __WALL_HPP__

# include "Map/AEntity.hpp"

namespace Map
{
  class Wall : public AEntity
  {
    Wall(Wall const &);
    Wall& operator=(Wall const &);

  public:
    Wall(int, int);
    ~Wall();

    bool action(Character::Character *);
    bool takeDmg(Statistics const &);

  };
};

#endif
