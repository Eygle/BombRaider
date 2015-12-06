#include "Map/XBomb.hpp"
#include "Map/XRessource.hpp"
#include "Character/Character.hpp"

//
// CTOR / DTOR
//

Map::XRessource::XRessource(int x, int y)
  : ARessource(X_RESSOURCE, x, y)
{
  this->_icon = &Data::getInstance()->imgs[Data::X_RESSOURCE_ICON];
}

Map::XRessource::~XRessource()
{
}

//
// PUBLIC FUNCTIONS
//

void	Map::XRessource::useEntity(Character::Character *origin)
{
  Map::XBomb *toLaunch = new Map::XBomb(origin);
  if (origin->dropBomb(toLaunch, toLaunch->getManaConso(), toLaunch->isDroppable()))
    this->_quantity--;
  else
    delete toLaunch;
}
