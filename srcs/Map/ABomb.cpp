#include "Map/ABomb.hpp"

//
// CTOR / DTOR / ASSIGN
//

Map::ABomb::ABomb(BombInfo const &info, Character::Character *origin,
		  Map::GameMap &map, std::list<Map::Explosion *> &explosions,
		  std::list<Map::ABomb *> &bombs)
  : AEntity(info.type, Map::BOMB, true, info.x, info.y), _origin(origin),
    _info(info), _map(map), _explosions(explosions), _bombs(bombs)
{
  this->_countdown.play();
}

Map::ABomb::~ABomb(){}

//
// GETTER
//

bool	Map::ABomb::isDroppable() const
{
  return (this->_info.isDroppable);
}

int	Map::ABomb::getManaConso() const
{
  return (this->_info.manaConso);
}

//
// PROTECTED FUNCTIONS
//

bool	Map::ABomb::addExplosion(int x, int y)
{
  if (x < 0 || x >= this->_map.getWidth()
      || y < 0 || y >= this->_map.getHeight())
    return (false);
  bool blocked = true;
  if (!this->_map.isWallAt(x, y))
    {
      blocked = this->_map.at(x, y).isBlocked();
      Map::Explosion *toAdd = new Explosion(this->_origin, this->_info.stats, x, y);
      this->_explosions.push_back(toAdd);
      this->_map.at(x, y).explode(toAdd);
    }
  return (!blocked);
}

//
// PUBLIC FUNCTIONS
//

bool	Map::ABomb::action(Character::Character *)
{
  this->_countdown.update();
  if (this->_countdown.getTotalElapsedTime() > this->_info.timeToExplode)
    {
      this->explode();
      return (true);
    }
  return (false);
}

bool	Map::ABomb::takeDmg(Statistics const &)
{
  this->explode();
  return (true);
}
