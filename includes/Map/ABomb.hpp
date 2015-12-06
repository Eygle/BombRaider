#ifndef __A_BOMB_HPP__
# define __A_BOMB_HPP__

# include <list>

# include "Map/GameMap.hpp"
# include "Map/BombInfo.hpp"
# include "Map/Explosion.hpp"
# include "GDL/Clock.hpp"

namespace Character
{
  class Character;
};

namespace Map
{
  class ABomb : public AEntity
  {
    ABomb(ABomb const &);
    ABomb& operator=(ABomb const &);

  protected:
    Character::Character	*_origin;
    BombInfo			_info;
    GameMap			&_map;
    std::list<Explosion *>	&_explosions;
    std::list<ABomb *>		&_bombs;
    gdl::Clock			_countdown;

    virtual void	explode() = 0;
    virtual bool	addExplosion(int, int);

  public:
    ABomb(BombInfo const &, Character::Character *,
	  GameMap &, std::list<Explosion *> &,
	  std::list<ABomb *> &);
    virtual ~ABomb();

    virtual bool	action(Character::Character *);
    virtual bool	takeDmg(Statistics const &);

    bool	isDroppable() const;
    int		getManaConso() const;
  };
};

#endif
