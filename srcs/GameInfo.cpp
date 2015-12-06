#include <map>

#include "GameInfo.hpp"

# include "Data.hpp"
# include "Character/Player.hpp"
# include "Character/AI.hpp"
# include "Champion/Minion.hpp"
# include "Map/ARessource.hpp"
# include "Map/Box.hpp"
# include "Map/Buff.hpp"
# include "Map/Wall.hpp"
# include "Map/MissileRessource.hpp"
# include "Map/RebonRessource.hpp"
# include "Map/XRessource.hpp"
# include "Map/FufuRessource.hpp"
# include "Map/MineRessource.hpp"
# include "Map/BrainRessource.hpp"
# include "Map/PiercingRessource.hpp"

GameInfo::GameInfo()
  : players(std::vector<Character::Player *>(NBR_MAX_PLAYER, NULL)), map(0)
{
  this->funcPtr[Map::MISSILE_RESSOURCE - Map::MISSILE_RESSOURCE] = &GameInfo::createMissileRessource;
  this->funcPtr[Map::REBON_RESSOURCE - Map::MISSILE_RESSOURCE] = &GameInfo::createRebonRessource;
  this->funcPtr[Map::X_RESSOURCE - Map::MISSILE_RESSOURCE] = &GameInfo::createXRessource;
  this->funcPtr[Map::FUFU_RESSOURCE - Map::MISSILE_RESSOURCE] = &GameInfo::createFufuRessource;
  this->funcPtr[Map::MINE_RESSOURCE - Map::MISSILE_RESSOURCE] = &GameInfo::createMineRessource;
  this->funcPtr[Map::BRAIN_RESSOURCE - Map::MISSILE_RESSOURCE] = &GameInfo::createBrainRessource;
  this->funcPtr[Map::PIERCING_RESSOURCE - Map::MISSILE_RESSOURCE] = &GameInfo::createPiercingRessource;

  this->funcPtr2[Map::MANA_POTION] = &GameInfo::createBuff;
  this->funcPtr2[Map::LIFE_POTION] = &GameInfo::createBuff;
  this->funcPtr2[Map::BUFF_MANA_MAX] = &GameInfo::createBuff;
  this->funcPtr2[Map::BUFF_POWER] = &GameInfo::createBuff;
  this->funcPtr2[Map::BUFF_RANGE] = &GameInfo::createBuff;
  this->funcPtr2[Map::BUFF_CRITICAL] = &GameInfo::createBuff;
  this->funcPtr2[Map::BUFF_DEFENSE] = &GameInfo::createBuff;
  this->funcPtr2[Map::BUFF_RESILIENCE] = &GameInfo::createBuff;
  this->funcPtr2[Map::BUFF_LIFE_MAX] = &GameInfo::createBuff;
  this->funcPtr2[Map::BUFF_SPEED] = &GameInfo::createBuff;
  this->funcPtr2[Map::CLASSIC_BOX] = &GameInfo::createBox;
  this->funcPtr2[Map::IRON_BOX] = &GameInfo::createBox;
  this->funcPtr2[Map::ULTIMA_BOX] = &GameInfo::createBox;
  this->funcPtr2[Map::CLASSIC_WALL] = &GameInfo::createWall;
  this->funcPtr2[Map::MISSILE_RESSOURCE] = &GameInfo::createMissile;
  this->funcPtr2[Map::REBON_RESSOURCE] = &GameInfo::createRebon;
  this->funcPtr2[Map::X_RESSOURCE] = &GameInfo::createX;
  this->funcPtr2[Map::FUFU_RESSOURCE] = &GameInfo::createFufu;
  this->funcPtr2[Map::BRAIN_RESSOURCE] = &GameInfo::createBrain;
  this->funcPtr2[Map::MINE_RESSOURCE] = &GameInfo::createMine;
  this->funcPtr2[Map::PIERCING_RESSOURCE] = &GameInfo::createPiercing;

  this->stats_.push_back("crit");
  this->stats_.push_back("def");
  this->stats_.push_back("hp");
  this->stats_.push_back("hpMax");
  this->stats_.push_back("mana");
  this->stats_.push_back("manaMax");
  this->stats_.push_back("power");
  this->stats_.push_back("range");
  this->stats_.push_back("resi");
  this->stats_.push_back("speed");

  this->gs_.push_back("bonusFrequency");
  this->gs_.push_back("boxFrequency");
  this->gs_.push_back("screenHeight");
  this->gs_.push_back("screenWidth");
  this->gs_.push_back("nbrPlayers");
  this->gs_.push_back("nbrAIs");
  this->gs_.push_back("minimap");
  this->gs_.push_back("language");
  this->gs_.push_back("mapHeight");
  this->gs_.push_back("mapWidth");

  this->champions_.push_back("corki");
  this->champions_.push_back("chogath");
  this->champions_.push_back("ryze");
  this->champions_.push_back("nocturne");
  this->champions_.push_back("fiddlestick");
}

GameInfo::~GameInfo()
{
}

bool	GameInfo::load()
{
  TiXmlDocument doc(".save.xml");

  std::map<int, Character::Character *>	charactMap;

  if (!doc.LoadFile() || !this->checkFile(doc))
    return false;

  TiXmlHandle root(&doc);
  TiXmlHandle	gs(root.FirstChild("GameSettings"));
  TiXmlHandle	players(root.FirstChild("PlayersList"));
  TiXmlHandle	ais(root.FirstChild("AIsList"));
  TiXmlHandle	map(root.FirstChild("Map"));
  TiXmlNode	*node;

  int	id, val;

  Data	*data = Data::getInstance();

  gs.FirstChild("bonusFrequency").Element()->QueryIntAttribute("value", &data->gameSettings.bonusFrequency);
  gs.FirstChild("boxFrequency").Element()->QueryIntAttribute("value", &data->gameSettings.boxFrequency);
  gs.FirstChild("screenHeight").Element()->QueryIntAttribute("value", &data->gameSettings.screenHeight);
  gs.FirstChild("screenWidth").Element()->QueryIntAttribute("value", &data->gameSettings.screenWidth);
  gs.FirstChild("nbrPlayers").Element()->QueryIntAttribute("value", &data->gameSettings.nbrPlayers);
  gs.FirstChild("nbrAIs").Element()->QueryIntAttribute("value", &data->gameSettings.nbrAI);
  data->gameSettings.minimap = std::string(gs.FirstChild("minimap").Element()->Attribute("value")) == "true" ? true : false;
  gs.FirstChild("language").Element()->QueryIntAttribute("value", &val);
  gs.FirstChild("mapHeight").Element()->QueryIntAttribute("value", &data->gameSettings.mapHeight);
  gs.FirstChild("mapWidth").Element()->QueryIntAttribute("value", &data->gameSettings.mapWidth);

  data->gameSettings.language = static_cast<Database::e_lang>(val);

  int	i = 0;
  for (TiXmlNode *p = players.FirstChild("Player").ToNode(); p; p = p->NextSibling())
    {
      std::string	champion;

      champion = p->FirstChild("Champion")->ToElement()->Attribute("name");
      p->FirstChild("ProfileId")->ToElement()->QueryIntAttribute("value", &id);
      this->players[i] = new Character::Player(*this, i);
      this->players[i]->load(champion, this->loadStats(p->FirstChild("Statistics")), data->db.getProfile(id));

      this->loadInventory(p->FirstChild("Inventory"), this->players[i]);

      p->FirstChild("Id")->ToElement()->QueryIntAttribute("value", &id);
      charactMap[id] = this->players[i];
      TiXmlNode	*status = p->FirstChild("Status");
      this->loadStatus(this->players[i], status);
      i++;
    }

  i = 0;
  for (TiXmlNode *ai = ais.FirstChild("AI").ToNode(); ai; ai = ai->NextSibling())
    {
      std::string name = ai->ToElement()->Attribute("name");
      Character::AI *toAdd = new Character::AI(*this);

      ai->FirstChild("Id")->ToElement()->QueryIntAttribute("value", &id);

      toAdd->setChampion(new Champion::Minion);
      toAdd->getProfile().name = name;
      toAdd->load(this->loadStats(ai->FirstChild("Statistics")), id);

      this->loadInventory(ai->FirstChild("Inventory"), toAdd);

      TiXmlNode	*status = ai->FirstChild("Status");
      this->loadStatus(toAdd, status);

      charactMap[id] = toAdd;
      this->AIs.push_back(toAdd);
      i++;
    }

  this->map = new Map::GameMap(data->gameSettings.mapWidth + 1, data->gameSettings.mapHeight + 1);

  int	x = 0, y = 0;
  for (TiXmlNode *p = map.FirstChild("MapCase").ToNode(); p; p = p->NextSibling())
    {
      for (TiXmlNode *c = p->FirstChild("ListCharacters"); c; c = c->NextSibling())
	if ((node = c->FirstChild("Character")))
	  {
	    node->ToElement()->QueryIntAttribute("id", &val);
	    this->map->at(x, y).addCharacter(charactMap[val]);
	  }

      for (TiXmlNode *it = p->FirstChild("ListItems"); it; it = it->NextSibling())
	if ((node = it->FirstChild("Item")))
	  {
	    node->ToElement()->QueryIntAttribute("type", &val);
	    Map::AEntity	*item;

	    if (val > Map::CLASSIC_EXPLOSION && val < Map::PIERCING_BOMB)
	      {
		Statistics	*stats = val < Map::CLASSIC_WALL
		  ? this->loadStats(node->FirstChild("Statistics")) : 0;

		item = (this->*(this->funcPtr2)[val])(static_cast<Map::e_item>(val), stats, x, y);
		this->map->at(x, y).addItem(item);
	      }
	  }
      y++;
      if (y == data->gameSettings.mapHeight + 1)
	{
	  y = 0;
	  x++;
	  if (x == data->gameSettings.mapWidth + 1)
	    break;
	}
     }

  std::cout << "Load complete" << std::endl;
  return true;
}

void	GameInfo::save()
{
  Data	*data = Data::getInstance();

  TiXmlDocument		doc;
  TiXmlDeclaration	*decl = new TiXmlDeclaration( "1.0", "", "" );
  TiXmlElement		*gs = new TiXmlElement("GameSettings");
  TiXmlElement		*playerList = new TiXmlElement("PlayersList");
  TiXmlElement		*aiList = new TiXmlElement("AIsList");
  TiXmlElement		*mapT = new TiXmlElement("Map");

  this->addGameSettings(gs, data);

  std::vector<Character::Player *>::iterator it;
  this->players.size();
  for (it = this->players.begin(); it != this->players.end() && *it; ++it)
    {
      TiXmlElement  *player = new TiXmlElement("Player");
      TiXmlElement  *profileId = new TiXmlElement("ProfileId");

      profileId->SetAttribute("value", (*it)->getTrueProfile()->id);

      player->LinkEndChild(profileId);
      playerList->LinkEndChild(player);

      this->addCharacterToSave(player, *it, true);
    }

  std::list<Character::AI *>::iterator it2;
  for (it2 = this->AIs.begin(); it2 != this->AIs.end() && *it2; ++it2)
    {
      TiXmlElement  *ai = new TiXmlElement("AI");

      ai->SetAttribute("name", (*it2)->getProfile().name);
      aiList->LinkEndChild(ai);
      this->addCharacterToSave(ai, *it2, false);
    }

  for (int w = 0; w < this->map->getWidth(); w++)
    {
      std::vector<Map::MapCase>			&h = (*this->map)[w];
      std::vector<Map::MapCase>::iterator	it;

      for (it = h.begin(); it != h.end(); ++it)
  	{
  	  TiXmlElement		*mapCase = new TiXmlElement("MapCase");

  	  this->addMapCase(*it, mapCase);
  	  mapT->LinkEndChild(mapCase);
  	}
    }

  doc.LinkEndChild(decl);
  doc.LinkEndChild(gs);
  doc.LinkEndChild(playerList);
  doc.LinkEndChild(aiList);
  doc.LinkEndChild(mapT);

  doc.SaveFile(".save.xml");
  std::cout << "Save complete" << std::endl;
}

void	GameInfo::loadStatus(Character::Character *c, TiXmlNode *status)
{
  float x, y, z;
  TiXmlElement *dir = status->FirstChild("Direction")->ToElement();

  dir->QueryFloatAttribute("x", &x);
  dir->QueryFloatAttribute("y", &y);
  dir->QueryFloatAttribute("z", &z);

  c->getNowState()->direction.x = x;
  c->getNowState()->direction.y = y;
  c->getNowState()->direction.z = z;

  TiXmlElement *pos = status->FirstChild("Position")->ToElement();

  pos->QueryFloatAttribute("x", &x);
  pos->QueryFloatAttribute("y", &y);
  pos->QueryFloatAttribute("z", &z);

  c->getNowState()->position.x = x;
  c->getNowState()->position.y = y;
  c->getNowState()->position.z = z;
}

Statistics	*GameInfo::loadStats(TiXmlNode *c)
{
  Statistics	*ret;
  int	        crit, def, hp, hp_max, mana, mana_max, power, range, resi, speed;

  c->FirstChild("crit")->ToElement()->QueryIntAttribute("value", &crit);
  c->FirstChild("def")->ToElement()->QueryIntAttribute("value", &def);
  c->FirstChild("hp")->ToElement()->QueryIntAttribute("value", &hp);
  c->FirstChild("hpMax")->ToElement()->QueryIntAttribute("value", &hp_max);
  c->FirstChild("mana")->ToElement()->QueryIntAttribute("value", &mana);
  c->FirstChild("manaMax")->ToElement()->QueryIntAttribute("value", &mana_max);
  c->FirstChild("power")->ToElement()->QueryIntAttribute("value", &power);
  c->FirstChild("range")->ToElement()->QueryIntAttribute("value", &range);
  c->FirstChild("resi")->ToElement()->QueryIntAttribute("value", &resi);
  c->FirstChild("speed")->ToElement()->QueryIntAttribute("value", &speed);
  ret = new Statistics(crit, def, hp, hp_max, mana, mana_max, power, range, resi, speed);

  return ret;
}

void	GameInfo::loadInventory(TiXmlNode *n, Character::Character *c)
{
  for (TiXmlNode *s = n->FirstChild("Slot"); s; s = s->NextSibling())
    {
      int	type, nbr;
      TiXmlElement	*elem = s->ToElement();
      elem->QueryIntAttribute("elem", &type);
      elem->QueryIntAttribute("nbr", &nbr);

      for (int i = 0; i < nbr; i++)
	c->takeItem((this->*(this->funcPtr)[type - Map::MISSILE_RESSOURCE])());
    }
}

bool	GameInfo::checkCharacter(TiXmlNode *c, bool isPlayer)
{
  TiXmlHandle   stats(c->FirstChild("Statistics"));
  TiXmlHandle   inv(c->FirstChild("Inventory"));
  TiXmlElement	*tmp;
  const char	*strTmp;
  int		val;

  if (isPlayer)
    {
      if (!(tmp = c->FirstChild("Champion")->ToElement()) || !(strTmp = tmp->Attribute("name")))
	return false;

      bool	find = false;
      for (unsigned int i = 0; i < this->champions_.size(); ++i)
	if (this->champions_[i] == strTmp)
	  find = true;
      if (!find)
	return false;
    }

  if (!(tmp = c->FirstChild("Id")->ToElement()) || tmp->QueryIntAttribute("value", &val))
    return false;
  for (unsigned int i = 0; i < this->stats_.size(); i++)
    if ( !(tmp = stats.FirstChild(this->stats_[i]).Element()) || tmp->QueryIntAttribute("value", &val))
      return false;

  for (TiXmlNode *s = inv.FirstChild("Slot").ToNode(); s; s = s->NextSibling())
    if (!(tmp = s->ToElement()) || tmp->QueryIntAttribute("elem", &val)
	|| tmp->QueryIntAttribute("nbr", &val))
      return false;

  return true;
}

bool	GameInfo::checkFile(TiXmlDocument &doc)
{
  TiXmlHandle	root(&doc);

  TiXmlHandle	gs(root.FirstChild("GameSettings"));
  TiXmlHandle	players(root.FirstChild("PlayersList"));
  TiXmlHandle	ais(root.FirstChild("AIsList"));
  TiXmlHandle	map(root.FirstChild("Map"));
  int		nbrPlayers, nbrAIs, w, h;
  TiXmlElement	*tmp;
  TiXmlNode	*nodeTmp;
  int		val = 0;
  const char	*strTmp;

  for (unsigned int i = 0; i < this->gs_.size(); i++)
    if (this->gs_[i] == "minimap" && (!(tmp = gs.FirstChild("minimap").Element()) || !(strTmp = tmp->Attribute("value"))))
      return false;
    else if (this->gs_[i] != "minimap" && (!(tmp = gs.FirstChild(this->gs_[i]).Element()) || tmp->QueryIntAttribute("value", &val)))
      return false;

  gs.FirstChild("nbrPlayers").Element()->QueryIntAttribute("value", &nbrPlayers);
  gs.FirstChild("nbrAIs").Element()->QueryIntAttribute("value", &nbrAIs);
  gs.FirstChild("mapWidth").Element()->QueryIntAttribute("value", &w);
  gs.FirstChild("mapHeight").Element()->QueryIntAttribute("value", &h);

  int	i = 0;
  for (TiXmlNode *p = players.FirstChild("Player").ToNode(); p; p = p->NextSibling())
    {
      if (!this->checkCharacter(p, true))
	return false;
      if (!(nodeTmp = p->FirstChild("ProfileId")) || !(tmp = nodeTmp->ToElement())
	  || tmp->QueryIntAttribute("value", &val))
	return false;
      i++;
    }
  if (i != nbrPlayers)
    return false;

  i = 0;
  for (TiXmlNode *ai = ais.FirstChild("AI").ToNode(); ai; ai = ai->NextSibling())
    {
      if (!this->checkCharacter(ai, false))
	return false;
      i++;
    }

  if (i != nbrAIs)
    return false;

  i = 0;
  for (TiXmlNode *p = map.FirstChild("MapCase").ToNode(); p; p = p->NextSibling())
    {
      for (TiXmlNode *c = p->FirstChild("ListCharacters"); c; c = c->NextSibling())
	{
	  if ((nodeTmp = c->FirstChild("Character")) &&
	      (!(tmp = nodeTmp->ToElement()) || tmp->QueryIntAttribute("id", &val)))
	    return false;
	}

      for (TiXmlNode *it = p->FirstChild("ListItems"); it; it = it->NextSibling())
	{
	  if ((nodeTmp = it->FirstChild("Item")))
	    {
	      if ((!(tmp = nodeTmp->ToElement()) || tmp->QueryIntAttribute("type", &val)))
		return false;
	      if (val > Map::CLASSIC_EXPLOSION && val < Map::CLASSIC_WALL)
		{
		  TiXmlHandle   stats = nodeTmp->FirstChild("Statistics");
		  for (unsigned int i = 0; i < this->stats_.size(); i++)
		    if (!(tmp = stats.FirstChild(this->stats_[i]).Element()) || tmp->QueryIntAttribute("value", &val))
		      return false;
		}
	    }
	  i++;
	}
    }

  int	total = (w+ 1) * (h + 1);
  if (i != total)
    return false;
  return true;
}

void	GameInfo::addGameSettings(TiXmlElement *gs, Data *data)
{
  std::ostringstream	oss;

  TiXmlElement	*bF = new TiXmlElement("bonusFrequency");
  TiXmlElement	*boxF = new TiXmlElement("boxFrequency");
  TiXmlElement	*scH = new TiXmlElement("screenHeight");
  TiXmlElement	*scW = new TiXmlElement("screenWidth");
  TiXmlElement	*nbP = new TiXmlElement("nbrPlayers");
  TiXmlElement	*nbAI = new TiXmlElement("nbrAIs");
  TiXmlElement	*miniM = new TiXmlElement("minimap");
  TiXmlElement	*lang = new TiXmlElement("language");
  TiXmlElement	*mapH = new TiXmlElement("mapHeight");
  TiXmlElement	*mapW = new TiXmlElement("mapWidth");

  bF->SetAttribute("value", data->gameSettings.bonusFrequency);
  boxF->SetAttribute("value", data->gameSettings.boxFrequency);
  scH->SetAttribute("value", data->gameSettings.screenHeight);
  scW->SetAttribute("value", data->gameSettings.screenWidth);
  nbP->SetAttribute("value", data->gameSettings.nbrPlayers);
  nbAI->SetAttribute("value", data->gameSettings.nbrAI);
  miniM->SetAttribute("value", data->gameSettings.minimap ? "true" : "false");
  lang->SetAttribute("value", data->gameSettings.language);
  mapH->SetAttribute("value", data->gameSettings.mapHeight);
  mapW->SetAttribute("value", data->gameSettings.mapWidth);

  gs->LinkEndChild(bF);
  gs->LinkEndChild(boxF);
  gs->LinkEndChild(scH);
  gs->LinkEndChild(scW);
  gs->LinkEndChild(nbP);
  gs->LinkEndChild(nbAI);
  gs->LinkEndChild(miniM);
  gs->LinkEndChild(lang);
  gs->LinkEndChild(mapH);
  gs->LinkEndChild(mapW);
}

void	GameInfo::addCharacterToSave(TiXmlElement *list, Character::Character *p, bool player)
{
  TiXmlElement  *inv = new TiXmlElement("Inventory");
  TiXmlElement	*id = new TiXmlElement("Id");
  TiXmlElement  *status = new TiXmlElement("Status");

  id->SetAttribute("value", p->getId());
  if (player)
    {
      TiXmlElement	*champion = new TiXmlElement("Champion");

      champion->SetAttribute("name", p->getChampion()->getName());
      list->LinkEndChild(champion);
    }


  std::vector<Map::ARessource *>::const_iterator	it;
  const std::vector<Map::ARessource *>			&inventory = p->getInventory();

  for (it = inventory.begin(); it != inventory.end() && *it; ++it)
    {
      TiXmlElement  *slot = new TiXmlElement("Slot");

      slot->SetAttribute("elem", (*it)->getType());
      slot->SetAttribute("nbr", (*it)->getQuantity());
      inv->LinkEndChild(slot);
    }

  this->saveStatus(p->getNowState(), status);

  Statistics const &stats = p->getAllStats();
  TiXmlElement  *st = new TiXmlElement("Statistics");
  this->saveStats(stats, st);

  list->LinkEndChild(status);
  list->LinkEndChild(inv);
  list->LinkEndChild(id);
  list->LinkEndChild(st);
}

void	GameInfo::saveStatus(Status *status, TiXmlElement  *dom)
{
  TiXmlElement	*dir = new TiXmlElement("Direction");
  TiXmlElement	*pos = new TiXmlElement("Position");

  dir->SetDoubleAttribute("x", status->direction.x);
  dir->SetDoubleAttribute("y", status->direction.y);
  dir->SetDoubleAttribute("z", status->direction.z);
  pos->SetDoubleAttribute("x", status->position.x);
  pos->SetDoubleAttribute("y", status->position.y);
  pos->SetDoubleAttribute("z", status->position.z);

  dom->LinkEndChild(dir);
  dom->LinkEndChild(pos);
}

void	GameInfo::saveStats(Statistics const &stats, TiXmlElement *st)
{
  TiXmlElement  *crit = new TiXmlElement("crit");
  TiXmlElement  *def = new TiXmlElement("def");
  TiXmlElement  *hp = new TiXmlElement("hp");
  TiXmlElement  *hpMax = new TiXmlElement("hpMax");
  TiXmlElement  *mana = new TiXmlElement("mana");
  TiXmlElement  *manaMax = new TiXmlElement("manaMax");
  TiXmlElement  *power = new TiXmlElement("power");
  TiXmlElement  *range = new TiXmlElement("range");
  TiXmlElement  *resi = new TiXmlElement("resi");
  TiXmlElement  *speed = new TiXmlElement("speed");

  crit->SetAttribute("value", stats.get(Statistics::CRITICAL));
  def->SetAttribute("value", stats.get(Statistics::DEFENSE));
  hp->SetAttribute("value", stats.get(Statistics::HP));
  hpMax->SetAttribute("value", stats.get(Statistics::HP_MAX));
  mana->SetAttribute("value", stats.get(Statistics::MANA));
  manaMax->SetAttribute("value", stats.get(Statistics::MANA_MAX));
  power->SetAttribute("value", stats.get(Statistics::POWER));
  range->SetAttribute("value", stats.get(Statistics::RANGE));
  resi->SetAttribute("value", stats.get(Statistics::RESILIENCE));
  speed->SetAttribute("value", stats.get(Statistics::SPEED));

  st->LinkEndChild(crit);
  st->LinkEndChild(def);
  st->LinkEndChild(hp);
  st->LinkEndChild(hpMax);
  st->LinkEndChild(mana);
  st->LinkEndChild(manaMax);
  st->LinkEndChild(power);
  st->LinkEndChild(range);
  st->LinkEndChild(resi);
  st->LinkEndChild(speed);
}

void	GameInfo::addMapCase(Map::MapCase &obj, TiXmlElement *mc)
{
  TiXmlElement	*charactList = new TiXmlElement("ListCharacters");
  TiXmlElement	*itemsList = new TiXmlElement("ListItems");

  std::list<Character::Character *>::const_iterator	it;
  for (it = obj.getCharacters().begin(); it != obj.getCharacters().end(); ++it)
    {
      TiXmlElement	*character = new TiXmlElement("Character");

      character->SetAttribute("id", (*it)->getId());
      charactList->LinkEndChild(character);
    }

  std::list<Map::AEntity *>::const_iterator	it2;
  for (it2 = obj.getItems().begin(); it2 != obj.getItems().end(); ++it2)
    {
      if ((*it2)->getType() > Map::CLASSIC_EXPLOSION && (*it2)->getType() < Map::PIERCING_BOMB)
	{
	  TiXmlElement	*item = new TiXmlElement("Item");

	  item->SetAttribute("type", (*it2)->getType());
	  if ((*it2)->getType() != Map::CLASSIC_WALL)
	    {
	      TiXmlElement  *st = new TiXmlElement("Statistics");

	      (*it2)->save(st, this);
	      item->LinkEndChild(st);
	    }
	  itemsList->LinkEndChild(item);
	}
    }

  mc->LinkEndChild(charactList);
  mc->LinkEndChild(itemsList);
}

Map::AEntity	*GameInfo::createBuff(Map::e_item item, Statistics *stats, int x, int y)
{
  return new Map::Buff(item, *stats, x, y);
}

Map::AEntity	*GameInfo::createBox(Map::e_item item, Statistics *stats, int x, int y)
{
  return new Map::Box(item, *stats, x, y);
}

Map::AEntity	*GameInfo::createWall(Map::e_item, Statistics *, int x, int y)
{
  return new Map::Wall(x, y);
}

Map::AEntity	*GameInfo::createMissile(Map::e_item, Statistics *, int x, int y)
{
  return new Map::MissileRessource(x, y);
}

Map::AEntity	*GameInfo::createRebon(Map::e_item, Statistics *, int x, int y)
{
  return new Map::RebonRessource(x, y);
}

Map::AEntity	*GameInfo::createX(Map::e_item, Statistics *, int x, int y)
{
  return new Map::XRessource(x, y);
}

Map::AEntity	*GameInfo::createFufu(Map::e_item, Statistics *, int x, int y)
{
  return new Map::FufuRessource(x, y);
}

Map::AEntity	*GameInfo::createMine(Map::e_item, Statistics *, int x, int y)
{
  return new Map::MineRessource(x, y);
}

Map::AEntity *GameInfo::createBrain(Map::e_item, Statistics *, int x, int y)
{
  return new Map::BrainRessource(x, y);
}

Map::AEntity	*GameInfo::createPiercing(Map::e_item, Statistics *, int x, int y)
{
  return new Map::PiercingRessource(x, y);
}

Map::ARessource	*GameInfo::createMissileRessource()
{
  return new Map::MissileRessource(0, 0);
}

Map::ARessource	*GameInfo::createRebonRessource()
{
  return new Map::RebonRessource(0, 0);
}

Map::ARessource	*GameInfo::createXRessource()
{
  return new Map::XRessource(0, 0);
}

Map::ARessource	*GameInfo::createFufuRessource()
{
  return new Map::FufuRessource(0, 0);
}

Map::ARessource	*GameInfo::createMineRessource()
{
  return new Map::MineRessource(0, 0);
}

Map::ARessource *GameInfo::createBrainRessource()
{
  return new Map::BrainRessource(0, 0);
}

Map::ARessource	*GameInfo::createPiercingRessource()
{
  return new Map::PiercingRessource(0, 0);
}
