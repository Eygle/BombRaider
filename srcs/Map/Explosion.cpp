#include "Map/Explosion.hpp"
#include "Character/Character.hpp"
#include "Data.hpp"

//
// CTOR / DTOR / ASSIGN
//

Map::Explosion::Explosion(Character::Character *origin, Statistics const &stats, int x, int y)
  : AEntity(Map::CLASSIC_EXPLOSION, Map::EXPLOSION, false, x, y),
    _origin(origin), _stats(stats), _coord(std::pair<int, int>(x, y))
{
  this->_now->position.y -= 0.5;
  this->_duration.play();
}

Map::Explosion::~Explosion(){}

//
// PUBLIC FUNCTIONS
//

bool	Map::Explosion::action(Character::Character *charac)
{
  if (!charac->isDead() && charac->takeDmg(this->_stats) && this->_origin)
    {
      if (charac->getType() == Character::Character::PLAYER)
	{
	  this->_origin->getProfile().nbrPlayersKilled++;
	  this->_origin->getProfile().score += 20;
	}
      else
	this->_origin->getProfile().nbrBotsKilled++;
      this->_origin->getProfile().score += 30;
      charac->getProfile().score -= 60;
    }
  return (false);
}

bool	Map::Explosion::takeDmg(Statistics const &attacker)
{
  this->_duration.reset();
  for (int i = 0, last = static_cast<int>(Statistics::LAST) ; i < last ; ++i)
    {
      Statistics::e_stat tmp = static_cast<Statistics::e_stat>(i);
      this->_stats.add(tmp, attacker.get(tmp));
    }
  return (false);
}

bool	Map::Explosion::isExtinct()
{
  this->_duration.update();
  return (this->_duration.getTotalElapsedTime() > EXPLOSION_TIME);
}

std::pair<int, int>	&Map::Explosion::getCoord()
{
  return (this->_coord);
}

Statistics const	&Map::Explosion::getStats()
{
  return (this->_stats);
}
