#ifndef GAMEINFO_H_
#define GAMEINFO_H_

# include <string>
# include <sstream>

# include "Database/Database.hpp"
# include "Map/ABomb.hpp"
# include "Map/Explosion.hpp"
# include "Map/GameMap.hpp"
# include "Map/ARessource.hpp"
//# include "Map/MapCase.hpp"
# include "Status.hpp"

# include "XML/ticpp.h"

namespace Character
{
  class AI;
  class Player;
}

# define NBR_MAX_PLAYER 4

struct Data;
namespace {class ARessource;};

struct GameInfo
{
  std::vector<Character::Player *>	players;
  Map::GameMap				*map;
  std::list<Map::ABomb *>		bombs;
  std::list<Character::AI *>		AIs;
  std::list<Map::Explosion *>		explosions;

  GameInfo();
  ~GameInfo();

  void	save();
  bool	load();

  void		saveStats(Statistics const &, TiXmlElement *);

private:
  GameInfo(GameInfo const &);

  std::vector<std::string>	stats_;
  std::vector<std::string>	gs_;
  std::vector<std::string>	champions_;

  Map::ARessource	*(GameInfo::*funcPtr[7])();
  Map::AEntity	*(GameInfo::*funcPtr2[28])(Map::e_item, Statistics *, int, int);

  Statistics	*loadStats(TiXmlNode *);
  void		loadStatus(Character::Character *, TiXmlNode *);
  void		loadInventory(TiXmlNode *, Character::Character *);
  bool		checkCharacter(TiXmlNode *, bool);
  bool		checkFile(TiXmlDocument &);
  void		saveStatus(Status *, TiXmlElement *);
  void		addGameSettings(TiXmlElement *, Data *);
  void		addCharacterToSave(TiXmlElement *, Character::Character *, bool);
  void		addMapCase(Map::MapCase &, TiXmlElement *);

  Map::AEntity	*createBuff(Map::e_item, Statistics *, int, int);
  Map::AEntity	*createBox(Map::e_item, Statistics *, int, int);
  Map::AEntity	*createWall(Map::e_item, Statistics *, int, int);
  Map::AEntity	*createMissile(Map::e_item, Statistics *, int, int);
  Map::AEntity	*createRebon(Map::e_item, Statistics *, int, int);
  Map::AEntity	*createX(Map::e_item, Statistics *, int, int);
  Map::AEntity	*createFufu(Map::e_item, Statistics *, int, int);
  Map::AEntity	*createMine(Map::e_item, Statistics *, int, int);
  Map::AEntity	*createBrain(Map::e_item, Statistics *, int, int);
  Map::AEntity	*createPiercing(Map::e_item, Statistics *, int, int);

  Map::ARessource	*createMissileRessource();
  Map::ARessource	*createRebonRessource();
  Map::ARessource	*createXRessource();
  Map::ARessource	*createFufuRessource();
  Map::ARessource	*createMineRessource();
  Map::ARessource	*createBrainRessource();
  Map::ARessource	*createPiercingRessource();
};

#endif
