#include "Map/FufuBomb.hpp"
#include "Map/FufuRessource.hpp"
#include "Character/Character.hpp"
#include "Data.hpp"

//
// CTOR / DTOR
//

Map::FufuRessource::FufuRessource(int x, int y)
  : ARessource(FUFU_RESSOURCE, x, y)
{
  this->_icon = &Data::getInstance()->imgs[Data::FUFU_RESSOURCE_ICON];

  this->mapSound_["corki"] = Sound::FUFU_CORKI_BOMB_NOISE;
  this->mapSound_["chogath"] = Sound::FUFU_CHOGATH_BOMB_NOISE;
  this->mapSound_["nocturne"] = Sound::FUFU_NOCTURNE_BOMB_NOISE;
  this->mapSound_["ryze"] = Sound::FUFU_RYZE_BOMB_NOISE;
  this->mapSound_["fiddlestick"] = Sound::FUFU_FIDDLESTICK_BOMB_NOISE;
}

Map::FufuRessource::~FufuRessource()
{
}

//
// PUBLIC FUNCTIONS
//

void	Map::FufuRessource::useEntity(Character::Character *origin)
{
  Map::FufuBomb *toLaunch = new Map::FufuBomb(origin);
  if (origin->dropBomb(toLaunch, toLaunch->getManaConso(), toLaunch->isDroppable()))
    {
      Data::getInstance()->soundManager->playSound(this->mapSound_[origin->getChampion()->getName()]);
      this->_quantity--;
    }
  else
    delete toLaunch;
}
