#include "Map/Wall.hpp"
#include "Graphic/Primitive.hpp"

//
// CTOR / DTOR / ASSIGN
//

Map::Wall::Wall(int x, int y)
  : AEntity(Map::CLASSIC_WALL, Map::WALL, true, x, y)
{
}

Map::Wall::~Wall()
{
}

//
// PUBLIC FUNCTIONS
//

bool	Map::Wall::action(Character::Character *)
{
  return (false);
}

bool	Map::Wall::takeDmg(Statistics const &)
{
  return (false);
}
