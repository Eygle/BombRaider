#include "Map/MissileBomb.hpp"
#include "Character/Character.hpp"
#include "Data.hpp"

//
// CTOR / DTOR
//

Map::MissileBomb::MissileBomb(Character::Character *origin, Clock *globalClock)
  : ABomb(BombInfo(5, Map::MISSILE_BOMB,
                   origin->getNowState()->position.x,
                   origin->getNowState()->position.z,
                   origin->getAllStats(), 5, false),
          origin, *origin->getGameInfo().map,
          origin->getGameInfo().explosions,
          origin->getGameInfo().bombs), _globalClock(globalClock)
{
  this->init(origin->getNowState()->direction.y);
}

Map::MissileBomb::MissileBomb(Character::Character *origin, Clock *globalClock, float angle)
  : ABomb(BombInfo(5, Map::MISSILE_BOMB,
                   origin->getNowState()->position.x,
                   origin->getNowState()->position.z,
                   origin->getAllStats(), 5, false),
          origin, *origin->getGameInfo().map,
          origin->getGameInfo().explosions,
          origin->getGameInfo().bombs), _globalClock(globalClock)
{
  this->init(angle);
}

Map::MissileBomb::~MissileBomb()
{
  Data::getInstance()->soundManager->stopSound(Sound::MISSILE_BOMB_NOISE);
}

//
// PRIVATE FUNCTIONS
//

void	Map::MissileBomb::init(float angle)
{
  this->_info.stats.add(Statistics::SPEED, 1);
  this->_isBlocking = false;
  this->_info.stats.add(Statistics::POWER, 10);
  this->_now->direction.y = angle;
  *this->_prev = *this->_now;
  this->_now->position.move_incr(this->_now->direction, 1.0);
  this->_info.x = this->_now->position.x;
  this->_info.y = this->_now->position.z;
  this->_map.at(this->_info.x, this->_info.y).addItem(this);
}

void	Map::MissileBomb::explode()
{
  Data::getInstance()->soundManager->stopSound(Sound::MISSILE_BOMB_NOISE);
  Data::getInstance()->soundManager->playSound(Sound::CLASSIC_BOMB_NOISE);
  this->_map.at(this->_info.x, this->_info.y).removeItem(this);
  this->_bombs.remove(this);
  this->addExplosion(this->_info.x, this->_info.y);
}

bool	Map::MissileBomb::move()
{
  float calc_dist = (this->_globalClock->getElapsedTime()
		     * (this->_info.stats.get(Statistics::SPEED) / 2.25));
  this->_map.at(this->_info.x, this->_info.y).removeItem(this);
  *this->_prev = *this->_now;
  this->_now->position.move_incr(this->_now->direction, calc_dist);
  this->_info.x = this->_now->position.x;
  this->_info.y = this->_now->position.z;
  if (this->_map.isPlayerAliveAt(this->_info.x, this->_info.y))
    return (false);
  return (this->_map.at(this->_info.x, this->_info.y).addItem(this));
}

//
// PUBLIC FUNCTIONS
//

bool	Map::MissileBomb::action(Character::Character *)
{
  this->_countdown.update();
  if (!this->move() || this->_countdown.getTotalElapsedTime() > this->_info.timeToExplode)
    {
      this->explode();
      return (true);
    }
  return (false);
}
