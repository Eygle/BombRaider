#include "math.h"
#include "Character/Character.hpp"
#include "Map/ClassicBomb.hpp"
#include "Map/ARessource.hpp"
#include "State/Arcade.hpp"

//
// CTOR / DTOR
//

Character::Character::Character(GameInfo &game_info, Champion::Champion *champion)
  : _gameInfo(game_info), _inventory(std::vector<Map::ARessource *>(3, NULL)),
    _stateNow(new Status), _statePrev(0), _selectedChampion(champion)
{
  static int id;
  this->_id = id;
  id++;
  this->_actions[State::JOYSTIC - State::MOVE] = &Character::Character::joystick;
  this->_actions[State::CLASSICAL_BOMB - State::MOVE] = &Character::Character::dropClassicalBomb;
  this->_actions[State::MOVE - State::MOVE] = &Character::Character::move;
  this->_actions[State::TURN - State::MOVE] = &Character::Character::turn;
  this->_actions[State::SKILL - State::MOVE] = &Character::Character::skill;
  this->_actions[State::SLOT_1 - State::MOVE] = &Character::Character::slot1;
  this->_actions[State::SLOT_2 - State::MOVE] = &Character::Character::slot2;
  this->_actions[State::SLOT_3 - State::MOVE] = &Character::Character::slot3;
  this->_actions[State::IDLE - State::MOVE] = &Character::Character::idle;
  this->_actions[State::CAMERA - State::MOVE] = &Character::Character::setJoystickCamera;
  this->_manaClock.play();
  this->_invulnerability.play();

  this->_mapSound["corki"] = Sound::CORKI_DMG_VOICE;
  this->_mapSound["chogath"] = Sound::CHOGATH_DMG_VOICE;
  this->_mapSound["nocturne"] = Sound::NOCTURNE_DMG_VOICE;
  this->_mapSound["ryze"] = Sound::RYZE_DMG_VOICE;
  this->_mapSound["fiddlestick"] = Sound::FIDDLE_DMG_VOICE;
}

Character::Character::~Character()
{
}

//
// SETTER
//

void	Character::Character::setClock(Clock *globalClock)
{
  this->_globalClock = globalClock;
}

void	Character::Character::setChampion(Champion::Champion *champ)
{
  this->_selectedChampion = champ;
  if (this->_selectedChampion)
    this->_stats = champ->getStats();
}

//
// GETTER
//

Clock	*Character::Character::getClock()
{
  return (this->_globalClock);
}

bool	Character::Character::isDead()
{
  return (this->_stats.get(Statistics::HP) == 0);
}

Status	 *Character::Character::getPrevState() const
{
  return	this->_statePrev;
}

Status	*Character::Character::getNowState() const
{
  return	this->_stateNow;
}

GameInfo	&Character::Character::getGameInfo() const
{
  return	this->_gameInfo;
}

Champion::Champion *Character::Character::getChampion() const
{
  return this->_selectedChampion;
}

std::vector<Map::ARessource *> const &Character::Character::getInventory() const
{
  return	this->_inventory;
}

int	Character::Character::getStat(Statistics::e_stat stat) const
{
  return	this->_stats.get(stat);
}

int	Character::Character::getId() const
{
  return	this->_id;
}

Statistics	const	&Character::Character::getAllStats() const
{
  return	this->_stats;
}

Profile	&Character::Character::getProfile()
{
  return this->_profile;
}

Character::Character::characterType	Character::Character::getType() const
{
  return this->_type;
}

//
// PRIVATE FUNCTIONS
//

void	Character::Character::resetInvulnerability()
{
  this->_invulnerability.reset();
  this->_invulnerability.play();
}

void	Character::Character::checkCase()
{
  this->_gameInfo.map->at(static_cast<int>(this->_stateNow->position.x),
			  static_cast<int>(this->_stateNow->position.z)).useItems(this);
}

void	Character::Character::dropClassicalBomb(float)
{
  Map::ClassicBomb *new_bomb = new Map::ClassicBomb(this);
  if (this->dropBomb(new_bomb, new_bomb->getManaConso(), new_bomb->isDroppable()) == false)
    delete new_bomb;
}

void	Character::Character::skill(float)
{
  if (this->_selectedChampion->isSkillReady()
      && this->_selectedChampion->actionSkill(this))
    {
      if (!this->_statePrev)
	this->_statePrev = new Status;
      *this->_statePrev = *this->_stateNow;
      this->_stateNow->animation = Status::SPELL;
    }
}

void	Character::Character::slot1(float)
{
  this->slot(0);
}

void	Character::Character::slot2(float)
{
  this->slot(1);
}

void	Character::Character::slot3(float)
{
  this->slot(2);
}

void	Character::Character::slot(int slot)
{
  if (!this->_inventory.at(slot))
    return ;
  this->_inventory.at(slot)->useEntity(this);
  if (this->_inventory.at(slot)->getQuantity() <= 0)
    {
      delete this->_inventory.at(slot);
      this->_inventory.at(slot) = 0;
    }
}

void	Character::Character::idle(float)
{
  if (!this->_statePrev)
    this->_statePrev = new Status;
  *this->_statePrev = *this->_stateNow;
  this->_stateNow->animation = Status::IDLE;
}

//
// MOVE-RELATED FUNCTIONS
//

float	calculDistance(Graphic::Vector3f pos, int x, int y)
{
  return (sqrt((pos.x - x) * (pos.x - x) + (pos.z - y) * (pos.z - y)));
}

void	Character::Character::moveOnMap(const Graphic::Vector3f &save)
{
  Map::MapCase &myCase = this->_gameInfo.map->at(static_cast<int>(this->_stateNow->position.x),
						 static_cast<int>(this->_stateNow->position.z));
  Map::MapCase &oldCase = this->_gameInfo.map->at(static_cast<int>(save.x),
						  static_cast<int>(save.z));
  Map::MapCase &adjCase1 = this->_gameInfo.map->at(static_cast<int>(this->_stateNow->position.x),
						   static_cast<int>(save.z));
  Map::MapCase &adjCase2 = this->_gameInfo.map->at(static_cast<int>(save.x),
						   static_cast<int>(this->_stateNow->position.z));
  bool block = false;

  if (static_cast<int>(this->_stateNow->position.x) != static_cast<int>(save.x)
      || static_cast<int>(this->_stateNow->position.z) != static_cast<int>(save.z))
    block = myCase.isBlocked();
  if (!block)
    {
      if (static_cast<int>(this->_stateNow->position.x) != static_cast<int>(save.x) &&
	  static_cast<int>(this->_stateNow->position.z) != static_cast<int>(save.z) &&
	  adjCase1.isBlocked() && adjCase2.isBlocked())
	{
	  this->_stateNow->position = save;
	  return;
	}
      this->_stateNow->animation = Status::RUN;
      oldCase.removeCharacter(this);
      myCase.addCharacter(this);
    }
  else
    {
      Graphic::Vector3f	tmp = save;
      if (static_cast<int>(this->_stateNow->position.x) != static_cast<int>(save.x))
	tmp.z += this->_stateNow->position.z - save.z;
      if (this->_gameInfo.map->at(tmp.x, tmp.z).isBlocked())
	tmp = save;
      if (static_cast<int>(this->_stateNow->position.z) != static_cast<int>(save.z) && adjCase2.isBlocked())
	tmp.x += this->_stateNow->position.x - save.x;
      if (this->_gameInfo.map->at(tmp.x, tmp.z).isBlocked())
	this->_stateNow->position = save;
      else
	{
	  oldCase.removeCharacter(this);
	  this->_gameInfo.map->at(tmp.x, tmp.z).addCharacter(this);
	  this->_stateNow->position = tmp;
	}
    }
}

bool	Character::Character::isThereCollisionAround(float distance)
{
  for (float i = 0.0; i <= 360.0; i += 1.0)
    {
      Graphic::Vector3f	tmp = this->_stateNow->position;
      tmp.move_incr(i, distance);
      if ((static_cast<int>(tmp.x) != static_cast<int>(this->_stateNow->position.x) ||
	   static_cast<int>(tmp.z) != static_cast<int>(this->_stateNow->position.z)) &&
	  this->_gameInfo.map->at(static_cast<int>(tmp.x),
				  static_cast<int>(tmp.z)).isBlocked())
	return true;
    }
  return false;
}

void	Character::Character::joystick(float angle)
{
  Graphic::Vector3f save = this->_stateNow->position;
  float calc_dist = this->_globalClock->getElapsedTime() * (this->_stats.get(Statistics::SPEED) / 2.75);

  if (!this->_statePrev)
    this->_statePrev = new Status;
  *this->_statePrev = *this->_stateNow;

  if (angle >= 135 && angle < 225)
    this->_stateNow->direction.y += 90;
  else if (angle >= 315 || angle < 45)
    this->_stateNow->direction.y -= 90;

  if (angle >= 225 && angle < 315)
    this->_stateNow->position.move_incr(this->_stateNow->direction, calc_dist / 2.0 * -1);
  else if ((angle >= 135 && angle < 225) || (angle >= 315 || angle < 45))
    this->_stateNow->position.move_incr(this->_stateNow->direction, calc_dist / 2.0);
  else
    this->_stateNow->position.move_incr(this->_stateNow->direction, calc_dist);

  if (angle >= 135 && angle < 225)
    this->_stateNow->direction.y -= 90;
  else if (angle >= 315 || angle < 45)
    this->_stateNow->direction.y += 90;

  this->moveOnMap(save);
}

void	Character::Character::setJoystickCamera(float angle)
{
  float	speed = this->_globalClock->getElapsedTime() * (this->_stats.get(Statistics::SPEED) * 2.75);

  if (angle >= 135 && angle < 225)
    this->_stateNow->direction.y += 6 * speed;
  else if (angle >= 315 || angle < 45)
    this->_stateNow->direction.y -= 6 * speed;
}

void	Character::Character::move(float angle)
{
  float calc_dist = this->_globalClock->getElapsedTime() * (this->_stats.get(Statistics::SPEED) / 2.75);
  Graphic::Vector3f save = this->_stateNow->position;

  if (!this->_statePrev)
    this->_statePrev = new Status;
  *this->_statePrev = *this->_stateNow;
  if (angle == -1)
    this->_stateNow->position.move_decr(this->_stateNow->direction, calc_dist / 2);
  else
    this->_stateNow->position.move_incr(this->_stateNow->direction, calc_dist);
  this->moveOnMap(save);
}

void	Character::Character::turn(float angle)
{
  if (!this->_statePrev)
    this->_statePrev = new Status;
  *this->_statePrev = *this->_stateNow;
  angle *= this->_stats.get(Statistics::SPEED);
  this->_stateNow->direction.y += this->_globalClock->getElapsedTime() * (angle / 0.075);
  if (this->_stateNow->direction.y < 0)
    this->_stateNow->direction.y += 360;
  else if (this->_stateNow->direction.y > 360)
    this->_stateNow->direction.y -= 360;
  this->_stateNow->animation = Status::IDLE;
}

//
// PUBLIC FUNCTIONS
//

bool	Character::Character::takeItem(Map::ARessource *to_add)
{
  std::vector<Map::ARessource *>::iterator freePlace = this->_inventory.end();
  for (std::vector<Map::ARessource *>::iterator it = this->_inventory.begin() ;
       it != this->_inventory.end() ; ++it)
    {
      if (*it && (*it)->getType() == to_add->getType())
	{
	  (*it)->add(2);
	  return (true);
	}
      else if (*it == 0 && freePlace == this->_inventory.end())
	freePlace = it;
    }
  if (freePlace == this->_inventory.end())
    return (false);
  *freePlace = to_add;
  return (true);
}

bool	Character::Character::takeDmg(Statistics const &attacker)
{
  Data::getInstance()->soundManager->playSound(this->_mapSound[this->_selectedChampion->getName()]);
  this->_invulnerability.update();
  if (this->_invulnerability.getTotalElapsedTime() < INVUL_TIME)
    return false;
  int dmg = State::Arcade::calcDmg(attacker, this->_stats);
  this->_stats.sub(Statistics::HP, dmg);
  if (this->isDead())
    {
      this->_stateNow->animation = Status::DEATH;
      return true;
    }
  this->resetInvulnerability();
  return false;
}

bool	Character::Character::dropBomb(Map::ABomb *to_drop, int manaConso, bool must_drop)
{
  Map::MapCase &myCase = this->_gameInfo.map->at(static_cast<int>(this->_stateNow->position.x),
						 static_cast<int>(this->_stateNow->position.z));
  if (!myCase.getItems().empty() || this->_stats.get(Statistics::MANA) < manaConso)
    return false;
  this->_stats.sub(Statistics::MANA, manaConso);
  if (!this->_statePrev)
    this->_statePrev = new Status;
  *this->_statePrev = *this->_stateNow;
  this->_stateNow->animation = Status::ATTACK;
  this->_gameInfo.bombs.push_front(to_drop);
  if (must_drop)
    myCase.addItem(to_drop);
  return true;
}

void	Character::Character::action(State::e_ArcadeAction action, float angle)
{
  (this->*(this->_actions)[action - State::MOVE])(angle);
}

void	Character::Character::update()
{
  this->checkCase();
  this->_manaClock.update();
  if (this->_manaClock.getTotalElapsedTime() > 0.33)
    {
      this->_stats.add(Statistics::MANA, 1);
      this->_manaClock.reset();
    }
  this->_selectedChampion->updateSkill(this);
}

Statistics::e_gauge_statut	Character::Character::setStat(Statistics::e_stat stat, int to_add)
{
  return this->_stats.add(stat, to_add);
}

void	Character::Character::subStats(Statistics const &to_sub)
{
  this->_stats.sub(to_sub);
}

void	Character::Character::addStats(Statistics const &to_add)
{
  this->_stats.add(to_add);
}
