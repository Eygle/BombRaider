#ifndef __X_BOMB_HPP__
# define __X_BOMB_HPP__

# include "Map/ABomb.hpp"

namespace Map
{
  class XBomb : public ABomb
  {
    XBomb(XBomb const &);
    XBomb& operator=(XBomb const &);

    void	explode();

  public:
    XBomb(Character::Character *);
    ~XBomb();
  };
};

#endif
