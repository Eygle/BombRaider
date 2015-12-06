#include "Map/MissileBomb.hpp"
#include "Data.hpp"
#include "Map/MissileRessource.hpp"
#include "Character/Character.hpp"

//
// CTOR / DTOR
//

Map::MissileRessource::MissileRessource(int x, int y)
  : ARessource(MISSILE_RESSOURCE, x, y)
{
  this->_icon = &Data::getInstance()->imgs[Data::MISSILE_RESSOURCE_ICON];
}

Map::MissileRessource::~MissileRessource()
{
  Data::getInstance()->soundManager->stopSound(Sound::MISSILE_BOMB_NOISE);
}

//
// PUBLIC FUNCTIONS
//

void	Map::MissileRessource::useEntity(Character::Character *origin)
{
  Map::MapCase &myCase = origin->getGameInfo().map->at(static_cast<int>(origin->getNowState()->position.x),
						       static_cast<int>(origin->getNowState()->position.z));

  if (origin->getStat(Statistics::MANA) >= 5 && myCase.getItems().empty())
    {
      Map::MissileBomb *toLaunch = new Map::MissileBomb(origin, origin->getClock());
      if (origin->dropBomb(toLaunch, toLaunch->getManaConso(), toLaunch->isDroppable()))
	{
	  Data::getInstance()->soundManager->playSound(Sound::MISSILE_BOMB_NOISE);
	  this->_quantity--;
	}
      else
	delete toLaunch;
    }
}
