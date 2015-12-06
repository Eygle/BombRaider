#ifndef __CLASSIC_BOMB_HPP__
# define __CLASSIC_BOMB_HPP__

# include "Map/ABomb.hpp"

namespace Map
{
  class ClassicBomb : public ABomb
  {
    ClassicBomb(ClassicBomb const &);
    ClassicBomb& operator=(ClassicBomb const &);

    void	explode();

  public:
    ClassicBomb(Character::Character *);
    ClassicBomb(int, int, GameMap &, std::list<Explosion *> &,
		std::list<ABomb *> &, Statistics const &);
    ~ClassicBomb();
  };
};

#endif
