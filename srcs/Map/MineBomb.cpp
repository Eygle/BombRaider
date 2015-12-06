#include "Map/MineBomb.hpp"
#include "Character/Character.hpp"

//
// CTOR / DTOR / ASSIGN
//

Map::MineBomb::MineBomb(Character::Character *origin)
  : ABomb(BombInfo(20, Map::CLASSIC_BOMB,
		   origin->getNowState()->position.x,
		   origin->getNowState()->position.z,
		   origin->getAllStats(), 10, true),
	  origin, *origin->getGameInfo().map,
	  origin->getGameInfo().explosions,
	  origin->getGameInfo().bombs)
{
  this->_info.stats.add(Statistics::POWER, 30);
  this->_now->position.y = -0.3;
  this->_isBlocking = false;
}

Map::MineBomb::~MineBomb()
{
}

//
// PRIVATE FUNCTIONS
//

void	Map::MineBomb::explode()
{
  Data::getInstance()->soundManager->playSound(Sound::CLASSIC_BOMB_NOISE);
  this->_map.at(this->_info.x, this->_info.y).removeItem(this);
  this->_bombs.remove(this);
  this->addExplosion(this->_info.x, this->_info.y);
}

bool	Map::MineBomb::action(Character::Character *target)
{
  this->_countdown.update();
  if (this->_countdown.getTotalElapsedTime() > this->_info.timeToExplode
      || (target && target != this->_origin))
    {
      this->explode();
      return (true);
    }
  return (false);
}
