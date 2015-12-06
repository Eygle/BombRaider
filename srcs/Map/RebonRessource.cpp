#include "Map/RebonBomb.hpp"
#include "Map/RebonRessource.hpp"
#include "Character/Character.hpp"

//
// CTOR / DTOR
//

Map::RebonRessource::RebonRessource(int x, int y)
  : ARessource(REBON_RESSOURCE, x, y)
{
  this->_icon = &Data::getInstance()->imgs[Data::REBON_RESSOURCE_ICON];
}

Map::RebonRessource::~RebonRessource()
{
}

//
// PUBLIC FUNCTIONS
//

void	Map::RebonRessource::useEntity(Character::Character *origin)
{
  Map::MapCase &myCase = origin->getGameInfo().map->at(static_cast<int>(origin->getNowState()->position.x),
						     static_cast<int>(origin->getNowState()->position.z));

  if (origin->getStat(Statistics::MANA) >= 10 && myCase.getItems().empty())
    {
      Map::RebonBomb *toLaunch = new Map::RebonBomb(origin, origin->getClock());
      if (origin->dropBomb(toLaunch, toLaunch->getManaConso(), toLaunch->isDroppable()))
	this->_quantity--;
      else
	delete toLaunch;
    }
}
