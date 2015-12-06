#include "GameInfo.hpp"
#include "Statistics.hpp"
#include "Character/Player.hpp"
#include "Map/BrainRessource.hpp"
#include "Character/Character.hpp"

//
// CTOR / DTOR
//

Map::BrainRessource::BrainRessource(int x, int y)
  : ARessource(BRAIN_RESSOURCE, x, y)
{
  this->_icon = &Data::getInstance()->imgs[Data::BRAIN_RESSOURCE_ICON];
}

Map::BrainRessource::~BrainRessource()
{
}

//
// PUBLIC FUNCTIONS
//

void	Map::BrainRessource::useEntity(Character::Character *origin)
{
  std::vector<Character::Player *>	&players = origin->getGameInfo().players;

  for (std::vector<Character::Player *>::iterator it = players.begin(); it != players.end(); it++)
    {
      if ((*it) && (*it)->getStat(Statistics::SPEED) > 0 && (*it) != origin)
	(*it)->setStat(Statistics::SPEED, ((*it)->getStat(Statistics::SPEED) * -2));
    }
  this->_quantity -= 2;
}
