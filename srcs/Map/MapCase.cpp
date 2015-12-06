#include <algorithm>

#include "Character/Character.hpp"
#include "Map/MapCase.hpp"
#include "Map/Buff.hpp"
#include "Map/MissileRessource.hpp"
#include "Character/Player.hpp"
#include "Statistics.hpp"
#include "Data.hpp"

#include "Map/RebonRessource.hpp"
#include "Map/XRessource.hpp"
#include "Map/PiercingRessource.hpp"
#include "Map/BrainRessource.hpp"
#include "Map/FufuRessource.hpp"
#include "Map/MineRessource.hpp"

//
// CTOR / DTOR / ASSIGN
//

Map::MapCase::MapCase()
  : _isExploding(false), _isBlocked(false)
{
  this->initBonusCreator();
}

Map::MapCase::MapCase(MapCase const &copy)
{
  this->_isExploding = copy._isExploding;
  this->_isBlocked = copy._isBlocked;
  this->_characters = copy._characters;
  this->_items = copy._items;
  this->initBonusCreator();
}

Map::MapCase& Map::MapCase::operator=(MapCase const &)
{
  return (*this);
}

Map::MapCase::~MapCase()
{
}

//
// GETTER
//

bool	Map::MapCase::isExploding() const
{
  return (this->_isExploding);
}

bool	Map::MapCase::isBlocked() const
{
  return (this->_isBlocked);
}

std::list<Map::AEntity *> &Map::MapCase::getItems()
{
  return (this->_items);
}

std::list<Character::Character *> &Map::MapCase::getCharacters()
{
  return this->_characters;
}

bool	Map::MapCase::isCategory(Map::e_category category) const
{
  for (std::list<AEntity *>::const_iterator it = this->_items.begin() ;
       it != this->_items.end() ; ++it)
    {
      if ((*it)->getCategory() == category)
	return (true);
    }
  return (false);
}

int	Map::MapCase::isPlayer(Character::Character const *character) const
{
  int	res = 0;
  for (std::list<Character::Character *>::const_iterator it = this->_characters.begin() ;
       it != this->_characters.end() ; ++it)
    {
      res = 1;
      if ((*it)->isDead())
	res = 3;
      else if (*it == character)
	res = 2;
    }
  return (res);
}

bool	Map::MapCase::isOtherPlayer(Character::Character const *character) const
{
  for (std::list<Character::Character *>::const_iterator it = this->_characters.begin() ;
       it != this->_characters.end() ; ++it)
    {
      if (*it != character && !(*it)->isDead())
	return (true);
    }
  return (false);
}

bool	Map::MapCase::isPlayerAlive() const
{
  for (std::list<Character::Character *>::const_iterator it = this->_characters.begin() ;
       it != this->_characters.end() ; ++it)
    {
      if (!(*it)->isDead())
	return (true);
    }
  return (false);
}

bool	Map::MapCase::isRealPlayer(std::vector<Character::Player *> const &players) const
{
  for (std::list<Character::Character *>::const_iterator it = this->_characters.begin() ;
       it != this->_characters.end() ; ++it)
    {
      if (!(*it)->isDead())
	{
	  for (std::vector<Character::Player *>::const_iterator it2 = players.begin() ;
	       it2 != players.end() ; ++it2)
	    {
	      if (*it == *it2)
		return (true);
	    }
	}
    }
  return (false);
}


//
// CREATE FUNCTIONS
//

void	Map::MapCase::initBonusCreator()
{
  this->_bonusCreator[0] = &Map::MapCase::addLifeMaxBuff;
  this->_bonusCreator[1] = &Map::MapCase::addManaMaxBuff;
  this->_bonusCreator[2] = &Map::MapCase::addManaPotion;
  this->_bonusCreator[3] = &Map::MapCase::addLifePotion;
  this->_bonusCreator[4] = &Map::MapCase::addPowerBuff;
  this->_bonusCreator[5] = &Map::MapCase::addRangeBuff;
  this->_bonusCreator[6] = &Map::MapCase::addCriticalBuff;
  this->_bonusCreator[7] = &Map::MapCase::addDefenseBuff;
  this->_bonusCreator[8] = &Map::MapCase::addResilienceBuff;
  this->_bonusCreator[9] = &Map::MapCase::addSpeedBuff;
  this->_bonusCreator[10] = &Map::MapCase::createRessource;
  this->_bonusCreator[11] = &Map::MapCase::addMissileRessource;
  this->_bonusCreator[12] = &Map::MapCase::addFufuRessource;
  this->_bonusCreator[13] = &Map::MapCase::addRebonRessource;
  this->_bonusCreator[14] = &Map::MapCase::addPiercingRessource;
  this->_bonusCreator[15] = &Map::MapCase::addMineRessource;
  this->_bonusCreator[16] = &Map::MapCase::addXRessource;
  this->_bonusCreator[17] = &Map::MapCase::addBrainRessource;
}

void	Map::MapCase::createRessource(int x, int y)
{
  int weightTab[7] = {20, 20, 20, 20, 20, 20, 20};
  int random = rand() % 140;

  for (int i = 0 ; i < 7 ; i++)
    {
      if (random < weightTab[i])
	{
	  (this->*(this->_bonusCreator[i + 11]))(x, y);
	  break;
	}
      random -= weightTab[i];
    }
}

void	Map::MapCase::createBonus(int x, int y)
{
  int weightTab[11] = {10, 25, 15, 15, 15, 30, 15, 10, 10, 15, 40};
  int random = rand() % 200;

  for(int i = 0 ; i < 11 ; i++)
    {
      if (random < weightTab[i])
  	{
  	  (this->*(this->_bonusCreator[i]))(x, y);
  	  break;
  	}
      random -= weightTab[i];
    }
}

void	Map::MapCase::addManaMaxBuff(int x, int y)
{
  Statistics	stats;

  stats.add(Statistics::MANA_MAX, 10);
  stats.add(Statistics::MANA, 10);
  this->addItem(new Buff(Map::BUFF_MANA_MAX, stats, x, y));
}

void	Map::MapCase::addLifeMaxBuff(int x, int y)
{
  Statistics	stats;

  stats.add(Statistics::HP_MAX, 10);
  stats.add(Statistics::HP, 10);
  this->addItem(new Buff(Map::BUFF_LIFE_MAX, stats, x, y));
}

void	Map::MapCase::addManaPotion(int x, int y)
{
  Statistics	stats(0, 0, 0, 0, 20);

  this->addItem(new Buff(Map::MANA_POTION, stats, x, y));
}

void	Map::MapCase::addLifePotion(int x, int y)
{
  Statistics	stats(0, 0, 20);

  this->addItem(new Buff(Map::LIFE_POTION, stats, x, y));
}

void	Map::MapCase::addPowerBuff(int x, int y)
{
  Statistics	stats;

  stats.add(Statistics::POWER, 5);
  this->addItem(new Buff(Map::BUFF_POWER, stats, x, y));
}

void	Map::MapCase::addRangeBuff(int x, int y)
{
  Statistics	stats;

  stats.add(Statistics::RANGE, 1);
  this->addItem(new Buff(Map::BUFF_RANGE, stats, x, y));
}

void	Map::MapCase::addCriticalBuff(int x, int y)
{
  Statistics	stats;

  stats.add(Statistics::CRITICAL, 2);
  this->addItem(new Buff(Map::BUFF_CRITICAL, stats, x, y));
}

void	Map::MapCase::addDefenseBuff(int x, int y)
{
  Statistics	stats;

  stats.add(Statistics::DEFENSE, 5);
  this->addItem(new Buff(Map::BUFF_DEFENSE, stats, x, y));
}

void	Map::MapCase::addResilienceBuff(int x, int y)
{
  Statistics	stats;

  stats.add(Statistics::RESILIENCE, 2);
  this->addItem(new Buff(Map::BUFF_RESILIENCE, stats, x, y));
}

void	Map::MapCase::addSpeedBuff(int x, int y)
{
  Statistics	stats;

  stats.add(Statistics::SPEED, 1);
  this->addItem(new Buff(Map::BUFF_SPEED, stats, x, y));
}

void	Map::MapCase::addMissileRessource(int x, int y)
{
  this->addItem(new MissileRessource(x, y));
}

void	Map::MapCase::addFufuRessource(int x, int y)
{
  this->addItem(new FufuRessource(x, y));
}

void	Map::MapCase::addRebonRessource(int x, int y)
{
  this->addItem(new RebonRessource(x, y));
}

void	Map::MapCase::addPiercingRessource(int x, int y)
{
  this->addItem(new PiercingRessource(x, y));
}
void	Map::MapCase::addMineRessource(int x, int y)
{
  this->addItem(new MineRessource(x, y));
}

void	Map::MapCase::addXRessource(int x, int y)
{
  this->addItem(new XRessource(x, y));
}

void	Map::MapCase::addBrainRessource(int x, int y)
{
  this->addItem(new BrainRessource(x, y));
}

//
// PRIVATE FUNCTIONS
//

void	 Map::MapCase::eraseItem(std::list<Map::AEntity *>::iterator &it)
{
  if (it == this->_items.begin())
    {
      this->_items.erase(it);
      it = this->_items.begin();
    }
  else
    {
      this->_items.erase(it);
      --it;
    }
}

//
// PUBLIC FUNCTIONS
//

void	Map::MapCase::explode(Map::Explosion *explosion)
{
  bool	needToPush = true;

  this->_isExploding = true;
  for (std::list<AEntity *>::iterator it = this->_items.begin() ; it != this->_items.end() ; ++it)
    {
      if ((*it)->getCategory() == Map::BOMB)
	{
	  (*it)->takeDmg(explosion->getStats());
	  this->_items.clear();
	  this->_isBlocked = false;
	  break;
	}
      else if ((*it)->takeDmg(explosion->getStats()))
	{
	  if ((*it)->isBlocking())
	    this->_isBlocked = false;
	  if ((*it)->getCategory() == Map::BOX
	      && (rand() % 100) < Data::getInstance()->gameSettings.bonusFrequency)
	    {
	      Graphic::Vector3f &pos = (*it)->getNowStatus()->position;
	      this->createBonus(static_cast<int>(pos.x), static_cast<int>(pos.z));
	    }
	  delete *it;
	  this->_items.remove(*it);
	  it = this->_items.begin();
	}
      else
	needToPush = false;
    }
  if (needToPush)
    this->_items.push_back(explosion);
}

void	Map::MapCase::useItems(Character::Character *charac)
{
  for (std::list<AEntity *>::iterator it = this->_items.begin() ; it != this->_items.end() ; ++it)
    {
      if ((*it)->getCategory() != Map::BOMB && (*it)->action(charac))
	{
	  if ((*it)->isBlocking())
	    this->_isBlocked = false;
	  if ((*it)->getCategory() != Map::RESSOURCE)
	    delete *it;
	  this->eraseItem(it);
	}
      else
	{
	  (*it)->action(charac);
	  it = this->_items.begin();
	}
    }
}

void	Map::MapCase::updateItems()
{
  for (std::list<AEntity *>::iterator it = this->_items.begin(); it != this->_items.end(); it++)
    (*it)->update();
}

void	Map::MapCase::extinguish()
{
  this->_isExploding = false;
  for (std::list<AEntity *>::iterator it = this->_items.begin() ; it != this->_items.end() ; it++)
    {
      if ((*it)->getCategory() == Map::EXPLOSION)
	{
	  this->_items.erase(it);
	  break;
	}
    }
}

//
// LIST-RELATED FUNCTIONS
//

void	Map::MapCase::addCharacter(Character::Character *toAdd)
{
  this->_characters.push_back(toAdd);
}

void	Map::MapCase::removeCharacter(Character::Character *toRemove)
{
  this->_characters.remove(toRemove);
}

bool	Map::MapCase::addItem(Map::AEntity *toAdd)
{
  if (this->_isBlocked)
    return (false);
  this->_items.push_back(toAdd);
  this->_isBlocked = toAdd->isBlocking();
  return (true);
}

void	Map::MapCase::removeItem(Map::AEntity *toRemove)
{
  if (toRemove->isBlocking())
    this->_isBlocked = false;
  this->_items.remove(toRemove);
}

void	Map::MapCase::clearItems()
{
  this->_items.clear();
  this->_isBlocked = false;
}
