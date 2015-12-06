#include "Map/RebonBomb.hpp"
#include "Character/Character.hpp"
#include "Data.hpp"

//
// CTOR / DTOR
//

Map::RebonBomb::RebonBomb(Character::Character *origin, Clock *globalClock)
  : ABomb(BombInfo(7, Map::REBON_BOMB,
                   origin->getNowState()->position.x,
                   origin->getNowState()->position.z,
                   origin->getAllStats(), 5, false),
          origin, *origin->getGameInfo().map,
          origin->getGameInfo().explosions,
          origin->getGameInfo().bombs), _globalClock(globalClock)
{
  this->init(origin->getNowState()->direction.y);
  this->_isAscending = true;
}

Map::RebonBomb::RebonBomb(Character::Character *origin, Clock *globalClock, float angle)
  : ABomb(BombInfo(7, Map::REBON_BOMB,
                   origin->getNowState()->position.x,
                   origin->getNowState()->position.z,
                   origin->getAllStats(), 5, false),
          origin, *origin->getGameInfo().map,
          origin->getGameInfo().explosions,
          origin->getGameInfo().bombs), _globalClock(globalClock)
{
  this->init(angle);
  this->_isAscending = true;
}

void	Map::RebonBomb::update()
{
  if (this->_isAscending == true)
    {
      this->_now->position.y += 0.1;
      if (this->_now->position.y >= 1.0)
	this->_isAscending = false;
    }
  else
    {
      this->_now->position.y -= 0.1;
      if (this->_now->position.y <= 0.5)
	{
	  Data::getInstance()->soundManager->playSound(Sound::REBON_BOMB_NOISE);
	  this->_isAscending = true;
	}
    }
}

Map::RebonBomb::~RebonBomb()
{
}

//
// PRIVATE FUNCTIONS
//

void	Map::RebonBomb::init(float angle)
{
  this->_isBlocking = false;
  this->_info.stats.add(Statistics::POWER, 10);
  this->_now->direction.y = angle;
  *this->_prev = *this->_now;
  this->_now->position.move_incr(this->_now->direction, 1.0);
  this->_info.x = this->_now->position.x;
  this->_info.y = this->_now->position.z;
  this->_map.at(this->_info.x, this->_info.y).addItem(this);
}

void	Map::RebonBomb::explode()
{
  int range = this->_info.stats.get(Statistics::RANGE);

  Data::getInstance()->soundManager->playSound(Sound::CLASSIC_BOMB_NOISE);
  this->_map.at(this->_info.x, this->_info.y).removeItem(this);
  this->_bombs.remove(this);
  for (int x = this->_info.x - 1 ; x >= this->_info.x - range
	 && this->addExplosion(x, this->_info.y) ; x--);
  for (int x = this->_info.x + 1 ; x <= this->_info.x + range
	 && this->addExplosion(x, this->_info.y) ; x++);
  this->addExplosion(this->_info.x, this->_info.y);
  for (int y = this->_info.y - 1 ; y >= this->_info.y - range
	 && this->addExplosion(this->_info.x, y) ; y--);
  for (int y = this->_info.y + 1 ; y <= this->_info.y + range
	 && this->addExplosion(this->_info.x, y) ; y++);
}

bool	Map::RebonBomb::move()
{
  float calc_dist = (this->_globalClock->getElapsedTime()
		     * (this->_info.stats.get(Statistics::SPEED) / 3.75));

  this->_map.at(this->_info.x, this->_info.y).removeItem(this);
  *this->_prev = *this->_now;
  this->_now->position.move_incr(this->_now->direction, calc_dist);
  this->_info.x = this->_now->position.x;
  this->_info.y = this->_now->position.z;
  if (this->_map.isPlayerAliveAt(this->_info.x, this->_info.y))
    return (false);
  if (this->_map.at(this->_info.x, this->_info.y).isBlocked())
    {
      this->_now->position.move_decr(this->_now->direction, calc_dist);
      this->_now->direction.y = static_cast<int>((this->_now->direction.y * 2) + 180.0) % 360;
      this->_info.x = this->_now->position.x;
      this->_info.y = this->_now->position.z;
    }
  this->_map.at(this->_info.x, this->_info.y).addItem(this);
  return true;
}

//
// PUBLIC FUNCTIONS
//

bool	Map::RebonBomb::action(Character::Character *)
{
  this->_countdown.update();
  if (!this->move() || this->_countdown.getTotalElapsedTime() > this->_info.timeToExplode)
    {
      this->explode();
      return (true);
    }
  return (false);
}
