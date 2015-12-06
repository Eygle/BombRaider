#include "Map/BombInfo.hpp"
#include "Map/EItems.hpp"

//
// CTOR / DTOR / ASSIGN
//

Map::BombInfo::BombInfo()
{
}

Map::BombInfo::BombInfo(float time, Map::e_item itemType, int posX, int posY,
			Statistics const &baseStats, int mana, bool drop)
  : timeToExplode(time), type(itemType), x(posX), y(posY),
    stats(baseStats), manaConso(mana), isDroppable(drop)
{
}

Map::BombInfo::BombInfo(Map::BombInfo const &other)
  : timeToExplode(other.timeToExplode), type(other.type),
    x(other.x), y(other.y), stats(other.stats),
    manaConso(other.manaConso), isDroppable(other.isDroppable)
{
}

Map::BombInfo& Map::BombInfo::operator=(Map::BombInfo const &other)
{
  if (this != &other)
    {
      this->timeToExplode = other.timeToExplode;
      this->type = other.type;
      this->x = other.x;
      this->y = other.y;
      this->stats = other.stats;
      this->manaConso = other.manaConso;
      this->isDroppable = other.isDroppable;
    }
  return (*this);
}

Map::BombInfo::~BombInfo()
{
}
