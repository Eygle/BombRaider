#include "Map/PiercingBomb.hpp"
#include "Map/PiercingRessource.hpp"
#include "Character/Character.hpp"

//
// CTOR / DTOR
//

Map::PiercingRessource::PiercingRessource(int x, int y)
  : ARessource(PIERCING_RESSOURCE, x, y)
{
  this->_icon = &Data::getInstance()->imgs[Data::PIERCING_RESSOURCE_ICON];
}

Map::PiercingRessource::~PiercingRessource()
{
}

//
// PUBLIC FUNCTIONS
//

void	Map::PiercingRessource::useEntity(Character::Character *origin)
{
  Map::PiercingBomb *toLaunch = new Map::PiercingBomb(origin);
  if (origin->dropBomb(toLaunch, toLaunch->getManaConso(), toLaunch->isDroppable()))
    this->_quantity--;
  else
    delete toLaunch;
}
