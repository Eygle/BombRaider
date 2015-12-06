#include <cstdlib>

#include "Map/GameMap.hpp"
#include "Map/Wall.hpp"
#include "Map/Box.hpp"
#include "Data.hpp"
#include "Character/Player.hpp"
#include "Character/AI.hpp"
#include "Graphic/Vector3f.hpp"

//
// CTOR / DTOR / ASSIGN
//

Map::GameMap::GameMap(int width, int height)
  : _height(height), _width(width),
    _map(std::vector<std::vector<Map::MapCase> >(width, std::vector<Map::MapCase>(height, Map::MapCase())))
{
  this->_boxCreator[0] = &GameMap::createClassicBox;
  this->_boxCreator[1] = &GameMap::createIronBox;
  this->_boxCreator[2] = &GameMap::createUltimaBox;
}

Map::GameMap::~GameMap()
{
  for (std::vector<std::vector<MapCase> >::iterator i = this->_map.begin();
       i != this->_map.end(); i++)
    (*i).clear();
  this->_map.clear();
}

//
// GETTER
//

int	Map::GameMap::getHeight() const
{
  return (this->_height);
}

int	Map::GameMap::getWidth() const
{
  return (this->_width);
}

Map::MapCase	&Map::GameMap::at(int x, int y)
{
  return (this->_map.at(x).at(y));
}

std::vector<Map::MapCase> &Map::GameMap::operator[](int x)
{
  return (this->_map.at(x));
}

bool	Map::GameMap::isWallAt(int x, int y) const
{
  return (this->_map.at(x).at(y).isCategory(Map::WALL));
}

int	Map::GameMap::isPlayerAt(int x, int y, const Character::Character *character) const
{
  return (this->_map.at(x).at(y).isPlayer(character));
}

bool	Map::GameMap::isPlayerAliveAt(int x, int y) const
{
  return (this->_map.at(x).at(y).isPlayerAlive());
}

bool	Map::GameMap::isBoxAt(int x, int y) const
{
  return (this->_map.at(x).at(y).isCategory(Map::BOX));
}

bool	Map::GameMap::isBombAt(int x, int y) const
{
  return (this->_map.at(x).at(y).isCategory(Map::BOMB));
}

bool	Map::GameMap::isBonusAt(int x, int y) const
{
  return (this->_map.at(x).at(y).isCategory(Map::BUFF)
	  || this->_map.at(x).at(y).isCategory(Map::RESSOURCE));
}

bool	Map::GameMap::isExplodingAt(int x, int y) const
{
  return (this->_map.at(x).at(y).isExploding());
}

//
// BOX-RELATED FUNCTIONS
//

void	Map::GameMap::createClassicBox(int x, int y)
{
  Statistics boxStats;

  boxStats.add(Statistics::HP_MAX, 1);
  boxStats.add(Statistics::HP, 1);
  this->_map[x][y].addItem(new Map::Box(CLASSIC_BOX, boxStats, x, y));
}

void	Map::GameMap::createIronBox(int x, int y)
{
  Statistics boxStats;

  boxStats.add(Statistics::HP_MAX, 30);
  boxStats.add(Statistics::HP, 30);
  this->_map[x][y].addItem(new Map::Box(IRON_BOX, boxStats, x, y));
}

void	Map::GameMap::createUltimaBox(int x, int y)
{
  Statistics boxStats;

  boxStats.add(Statistics::HP_MAX, 100);
  boxStats.add(Statistics::HP, 100);
  this->_map[x][y].addItem(new Map::Box(ULTIMA_BOX, boxStats, x, y));
}

void	Map::GameMap::updateMap()
{
  for (std::vector<std::vector<MapCase> >::iterator it = this->_map.begin(); it != this->_map.end(); it++)
    for (std::vector<MapCase>::iterator iter = (*it).begin(); iter != (*it).end(); iter++)
      (*iter).updateItems();
}

void	Map::GameMap::createRandomBox(int x, int y)
{
  int weightTab[3] = {65, 30, 5};
  int random = rand() % 100;

  for(int i = 0 ; i < 3 ; i++)
    {
      if (random < weightTab[i])
	{
	  (this->*(this->_boxCreator[i]))(x, y);
	  break;
	}
      random -= weightTab[i];
    }
}

//
// PRIVATE FUNCTIONS
//

bool	Map::GameMap::isItAround(Character::Character const *charac, int x, int y)
{
  Graphic::Vector3f &pos = charac->getNowState()->position;
  int posX = static_cast<int>(pos.x), posY = static_cast<int>(pos.z);
  return ((posX == x && (posY >= y - 1 && posY <= y + 1))
	  || (posY == y && (posX >= x - 1 && posX <= x + 1)));
}

bool	Map::GameMap::isThereSomeoneAround(int x, int y, GameInfo const &infos)
{
  for (std::vector<Character::Player *>::const_iterator it = infos.players.begin() ;
       it != infos.players.end() ; it++)
    {
      if (*it && this->isItAround(*it, x, y))
	return (true);
    }
  for (std::list<Character::AI *>::const_iterator it = infos.AIs.begin() ;
       it != infos.AIs.end() ; it++)
    {
      if (this->isItAround(*it, x, y))
	return (true);
    }
  return (false);
}

//
// PUBLIC FUNCTIONS
//

void	Map::GameMap::generate(GameInfo const &infos)
{
  Data	*datas = Data::getInstance();

  for (int x = 0 ; x < this->_width ; x++)
    {
      for (int y = 0 ; y < this->_height ; y++)
	{
	  if (y == 0 || y == this->_height - 1 || x == 0
	      || x == this->_width - 1 || (!(x % 2) && !(y % 2)))
	    this->_map[x][y].addItem(new Map::Wall(x, y));
	  else if (!this->isThereSomeoneAround(x, y, infos)
		   && ((rand() % 100) + 1) < datas->gameSettings.boxFrequency)
	    this->createRandomBox(x, y);
	}
    }
}
