#ifndef __MINE_BOMB_HPP__
# define __MINE_BOMB_HPP__

# include "Map/ABomb.hpp"

namespace Map
{
  class MineBomb : public ABomb
  {
    MineBomb(MineBomb const &);
    MineBomb& operator=(MineBomb const &);

    void	explode();

  public:
    MineBomb(Character::Character *);
    ~MineBomb();

    bool	action(Character::Character *);
  };
};

#endif
