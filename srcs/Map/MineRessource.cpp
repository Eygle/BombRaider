#include "Map/MineBomb.hpp"
#include "Map/MineRessource.hpp"
#include "Character/Character.hpp"

//
// CTOR / DTOR
//

Map::MineRessource::MineRessource(int x, int y)
  : ARessource(MINE_RESSOURCE, x, y)
{
  this->_icon = &Data::getInstance()->imgs[Data::MINE_RESSOURCE_ICON];
}

Map::MineRessource::~MineRessource()
{
}

//
// PUBLIC FUNCTIONS
//

void	Map::MineRessource::useEntity(Character::Character *origin)
{
  Map::MineBomb *toLaunch = new Map::MineBomb(origin);
  if (origin->dropBomb(toLaunch, toLaunch->getManaConso(), toLaunch->isDroppable()))
    this->_quantity--;
  else
    delete toLaunch;
}
