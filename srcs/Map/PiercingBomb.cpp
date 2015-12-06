#include "Map/PiercingBomb.hpp"
#include "Character/Character.hpp"

//
// CTOR / DTOR / ASSIGN
//

Map::PiercingBomb::PiercingBomb(Character::Character *origin)
  : ABomb(BombInfo(3, Map::PIERCING_BOMB,
		   origin->getNowState()->position.x,
		   origin->getNowState()->position.z,
		   origin->getAllStats(), 10, true),
	  origin, *origin->getGameInfo().map,
	  origin->getGameInfo().explosions,
	  origin->getGameInfo().bombs)
{
  this->_info.stats.add(Statistics::POWER, 10);
}

Map::PiercingBomb::~PiercingBomb()
{
}

//
// PRIVATE FUNCTIONS
//

void	Map::PiercingBomb::explode()
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

bool	Map::PiercingBomb::addExplosion(int x, int y)
{
  if (x < 0 || x >= this->_map.getWidth()
      || y < 0 || y >= this->_map.getHeight())
    return (false);
  Map::Explosion *toAdd = new Explosion(this->_origin, this->_info.stats, x, y);
  this->_explosions.push_back(toAdd);
  this->_map.at(x, y).explode(toAdd);
  return (true);
}
