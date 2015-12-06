#include <math.h>
#include "Character/AI.hpp"
#include "Character/Player.hpp"

#define SQR(x) ((x) * (x))
#define ABS(x) (((x) > 0) ? (x) : (-(x)))

//
// CTOR / DTOR
//

Character::AI::AI(GameInfo &gameInfo)
  : Character(gameInfo)
{
  Data	*datas = Data::getInstance();
  this->_difficulty = datas->gameSettings.difficulty;
}

Character::AI::~AI()
{
}

//
// AI-ACTION
//

Character::AI::Action::Action(State::e_ArcadeAction arcadeAction, float actionValue)
  : action(arcadeAction), value(actionValue)
{
}

//
// PRIVATE FUNCTIONS
//

void	Character::AI::push(State::e_ArcadeAction action, float value)
{
  this->_todo.push(AI::Action(action, value));
}

float	Character::AI::calcDistance(const Graphic::Vector3f &p1, const Graphic::Vector3f &p2) const
{
  return sqrt(SQR(p1.x - p2.x) + SQR(p1.z - p2.z));
}

bool	Character::AI::isDangerousPlace(Graphic::Vector3f &start, int direction, int how_far) const
{
  if (how_far == 6)
    return false;
  if (this->_gameInfo.map->isBombAt(start.x, start.z))
    return true;
  if (this->_gameInfo.map->isExplodingAt(start.x, start.z) && this->_stateNow->position != start)
    return true;
  if (this->_gameInfo.map->at(start.x, start.z).isBlocked())
    return false;
  if (direction == -1)
    for (int i = 0; i < 4; i++)
      {
	Graphic::Vector3f tmp = start + Graphic::Vector3f((!i) - (i == 2), 0,  (i == 1) - (i == 3));
	if (isDangerousPlace(tmp, i))
	  return true;
      }
  else
    {
      Graphic::Vector3f tmp = start + Graphic::Vector3f((!direction) - (direction == 2),
							0, (direction == 1) - (direction == 3));
      return (isDangerousPlace(tmp, direction, how_far + 1));
    }
  return false;
}

Graphic::Vector3f    Character::AI::findSafePlace(Graphic::Vector3f &start,
						  int from,
						  int how_far) const
{
  Graphic::Vector3f	ret;
  if ((this->_gameInfo.map->at(start.x, start.z).isBlocked() && this->_stateNow->position != start)
      || how_far == 10)
    return start;
  if (!this->isDangerousPlace(start))
    return start;
  ret = start;
  for (int i = 0; i < 4; i++)
    {
      if (i == from)
        continue;
      Graphic::Vector3f tmp = start + Graphic::Vector3f((!i) - (i == 2), 0,  (i == 1) - (i == 3));
      if (this->calcDistance(tmp, this->_stateNow->position) > 5)
	continue;
      Graphic::Vector3f newCase = findSafePlace(tmp, (i + 2) % 4, how_far + 1);
      if (ret == start  || this->calcDistance(ret, start) > this->calcDistance(newCase, start))
	ret = newCase;
    }
  return (ret);
}


Graphic::Vector3f    Character::AI::findClosestItem(Graphic::Vector3f &start,
						    int from,
						    int how_far) const
{
  Graphic::Vector3f	ret;
  if ((this->_gameInfo.map->at(start.x, start.z).isBlocked() && this->_stateNow->position != start)
      || how_far == 10)
    return start;
  if (this->_gameInfo.map->isBonusAt(start.x, start.z) || how_far == 10)
    return (start);
  ret = start;
  for (int i = 0; i < 4; i++)
    {
      if (i == from)
        continue;
      Graphic::Vector3f tmp = start + Graphic::Vector3f((!i) - (i == 2), 0,  (i == 1) - (i == 3));
      if (this->calcDistance(tmp, this->_stateNow->position) > 3.0)
	continue;
      Graphic::Vector3f newCase = findClosestItem(tmp, (i + 2) % 4, how_far + 1);
      if (this->calcDistance(ret, start) > this->calcDistance(newCase, start) && newCase != start)
	ret = newCase;
    }
  return (ret);
}

Graphic::Vector3f	Character::AI::findClosestChamp(Graphic::Vector3f &start)
{
  Graphic::Vector3f	ret = this->_gameInfo.players[0]->getNowState()->position;
  
  for (std::vector<Player *>::iterator it = this->_gameInfo.players.begin();
       it != this->_gameInfo.players.end();
       it++)
    if (*it && calcDistance(start, (*it)->getNowState()->position) < calcDistance(start, ret))
	ret = (*it)->getNowState()->position;
  return (ret);
}

void	Character::AI::calculAction()
{
  Graphic::Vector3f objectif = this->_stateNow->position;
  if (this->isDangerousPlace(this->_stateNow->position))
    objectif = this->findSafePlace(this->_stateNow->position, -1, 0);
  else
    {
      if (this->_difficulty > 1)
	{
	  Graphic::Vector3f	item = this->findClosestItem(this->_stateNow->position);
	  objectif = (item != this->_stateNow->position) ? item : this->findClosestChamp(this->_stateNow->position);
	}
      else
	objectif = this->findClosestChamp(this->_stateNow->position);
    }
  float diffX = this->_stateNow->position.x - objectif.x;
  float diffY = this->_stateNow->position.z - objectif.z;
  Graphic::Vector3f &pos = this->_stateNow->position;

  if (diffX > 1 &&
      !this->_gameInfo.map->at(pos.x - 1, pos.z).isBlocked())
    this->_stateNow->direction.y = 0;
  else if (diffX < -1 &&
	   !this->_gameInfo.map->at(pos.x + 1, pos.z).isBlocked())
    this->_stateNow->direction.y = 180;
  else if (diffY < -1 &&
	   !this->_gameInfo.map->at(pos.x, pos.z + 1).isBlocked())
    this->_stateNow->direction.y = 90;
  else if (diffY > 1 &&
	   !this->_gameInfo.map->at(pos.x, pos.z - 1).isBlocked())
    this->_stateNow->direction.y = 270;
  if (this->_difficulty > 2 &&
      this->_gameInfo.map->at(objectif.x, objectif.z).isRealPlayer(this->_gameInfo.players)
      && this->calcDistance(objectif, pos) < this->_stats.get(Statistics::RANGE))
    this->push(State::CLASSICAL_BOMB, 0.0);
  else if (this->_gameInfo.map->at(pos.x, pos.z).isRealPlayer(this->_gameInfo.players))
    this->push(State::CLASSICAL_BOMB, 0.0);
  else if (this->_gameInfo.map->at(pos.x, pos.z).isOtherPlayer(this) &&
	   this->_difficulty != 4)
    this->push(State::CLASSICAL_BOMB, 0.0);
  else
    this->push(State::MOVE, 0.0);
}


//
// PUBLIC FUNCTIONS
//

Character::AI::Action const	&Character::AI::front() const
{
  return (this->_todo.front());
}

void	Character::AI::pop()
{
  this->_todo.pop();
}

void	Character::AI::load(Statistics *stats, int id)
{
  this->_id = id;
  this->_stats = *stats;
}
