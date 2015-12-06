#include "Map/Buff.hpp"
#include "Character/Character.hpp"

//
// CTOR / DTOR / ASSIGN
//

Map::Buff::Buff(Map::e_item type, Statistics const &stats, int x, int y)
  : AEntity(type, Map::BUFF, false, x, y), _stats(stats)
{
}

Map::Buff::~Buff()
{
}

//
// PUBLIC FUNCTIONS
//

void	Map::Buff::update()
{
  this->_now->direction.x = (this->_now->direction.x + 1.5);
  this->_now->direction.x += (this->_now->direction.x < 0) * 360 - 360 * (this->_now->direction.x > 360);
  this->_now->direction.y = (this->_now->direction.y + 1.5);
  this->_now->direction.x += (this->_now->direction.y < 0) * 360 - 360 * (this->_now->direction.y > 360);
  this->_now->direction.z = (this->_now->direction.z + 1.5);
  this->_now->direction.x += (this->_now->direction.z < 0) * 360 - 360 * (this->_now->direction.z > 360);
  if (!this->_prev)
    this->_prev = new Status(*this->_now);
}

bool	Map::Buff::action(Character::Character *charac)
{
  charac->addStats(this->_stats);
  return (true);
}

bool	Map::Buff::takeDmg(Statistics const &)
{
  return (true);
}

void	Map::Buff::save(TiXmlElement *dom, GameInfo *info)
{
  info->saveStats(this->_stats, dom);
}
