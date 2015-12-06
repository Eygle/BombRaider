#include "Map/XBomb.hpp"
#include "Character/Character.hpp"

//
// CTOR / DTOR / ASSIGN
//

Map::XBomb::XBomb(Character::Character *origin)
  : ABomb(BombInfo(3, Map::X_BOMB,
		   origin->getNowState()->position.x,
		   origin->getNowState()->position.z,
		   origin->getAllStats(), 10, true),
	  origin, *origin->getGameInfo().map,
	  origin->getGameInfo().explosions,
	  origin->getGameInfo().bombs)
{
  this->_info.stats.add(Statistics::POWER, 10);
}

Map::XBomb::~XBomb()
{
}

//
// PRIVATE FUNCTIONS
//

void	Map::XBomb::explode()
{
  int range = this->_info.stats.get(Statistics::RANGE);
  Data::getInstance()->soundManager->playSound(Sound::CLASSIC_BOMB_NOISE);
  this->_map.at(this->_info.x, this->_info.y).removeItem(this);
  this->_bombs.remove(this);

  for (int x = this->_info.x - 1, y = this->_info.y - 1 ;
       x >= this->_info.x - range && this->addExplosion(x, y) ;
       x--, y--);
  for (int x = this->_info.x + 1, y = this->_info.y - 1 ;
       x <= this->_info.x + range && this->addExplosion(x, y) ;
       x++, y--);
  this->addExplosion(this->_info.x, this->_info.y);
  for (int x = this->_info.x - 1, y = this->_info.y + 1 ;
       x >= this->_info.x - range && this->addExplosion(x, y) ;
       x--, y++);
  for (int x = this->_info.x + 1, y = this->_info.y + 1 ;
       x <= this->_info.x + range && this->addExplosion(x, y) ;
       x++, y++);
}
