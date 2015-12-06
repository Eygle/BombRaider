#include "Map/Box.hpp"
#include "State/Arcade.hpp"

//
// CTOR / DTOR / ASSIGN
//

Map::Box::Box(Map::e_item type, Statistics const &stats, int x, int y)
  : AEntity(type, Map::BOX, true, x, y), _stats(stats)
{
}

Map::Box::~Box()
{
}

//
// PUBLIC FUNCTIONS
//

bool	Map::Box::action(Character::Character *)
{
  return (false);
}

bool	Map::Box::takeDmg(Statistics const &attacker)
{
  this->_invulnerability.update();
  if (this->_invulnerability.getTotalElapsedTime() > EXPLOSION_TIME)
    {
      this->_invulnerability.pause();
      this->_invulnerability.reset();
    }
  else if (this->_invulnerability.getTotalElapsedTime() > 0)
    return (false);
  this->_invulnerability.play();
  this->_stats.sub(Statistics::HP, State::Arcade::calcDmg(attacker, this->_stats));
  return (this->_stats.get(Statistics::HP) <= 0);
}

void	Map::Box::save(TiXmlElement *dom, GameInfo *info)
{
  info->saveStats(this->_stats, dom);
}
