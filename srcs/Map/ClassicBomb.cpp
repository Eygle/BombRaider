#include "Map/ClassicBomb.hpp"
#include "Character/Character.hpp"

//
// CTOR / DTOR / ASSIGN
//

Map::ClassicBomb::ClassicBomb(Character::Character *origin)
  : ABomb(BombInfo(3, Map::CLASSIC_BOMB,
		   origin->getNowState()->position.x,
		   origin->getNowState()->position.z,
		   origin->getAllStats(), 10, true),
	  origin, *origin->getGameInfo().map,
	  origin->getGameInfo().explosions,
	  origin->getGameInfo().bombs)
{
  this->_info.stats.add(Statistics::POWER, 10);
}

Map::ClassicBomb::ClassicBomb(int x, int y, Map::GameMap &map,
			      std::list<Map::Explosion *> &explosions,
			      std::list<Map::ABomb *> &bombs,
			      Statistics const &stats)
  : ABomb(BombInfo(3, Map::CLASSIC_BOMB, x, y, stats, 10, true),
	  0, map, explosions, bombs)
{
  this->_info.stats.add(Statistics::POWER, 10);
}

Map::ClassicBomb::~ClassicBomb()
{
}

//
// PRIVATE FUNCTIONS
//

void	Map::ClassicBomb::explode()
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
