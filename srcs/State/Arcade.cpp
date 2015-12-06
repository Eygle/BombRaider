#include <cstdlib>

#include "State/Arcade.hpp"
#include "Character/Player.hpp"
#include "Character/AI.hpp"
#include "Data.hpp"

//
// CTOR / DTOR
//

State::Arcade::Arcade()
{
  this->_actionMaker[MOVE_UP - MOVE_UP] = &State::Arcade::move_up;
  this->_actionMaker[MOVE_DOWN - MOVE_UP] = &State::Arcade::move_down;
  this->_actionMaker[TURN_LEFT - MOVE_UP] = &State::Arcade::turn_left;
  this->_actionMaker[TURN_RIGHT - MOVE_UP] = &State::Arcade::turn_right;
  this->_endOfGame = false;
}

State::Arcade::~Arcade()
{
}

//
// ACTION_PARAM FUNCTIONS
//

State::Arcade::ActionParam::ActionParam(Character::Player *plr, State::e_ArcadeAction act)
  : isPressed(false), player(plr), action(act), value(0.0)
{
}

State::Arcade::ActionParam::~ActionParam()
{
}

//
// RESET-RELATED FUNCTIONS
//

void	State::Arcade::resetPlayer()
{
  for (std::vector<Character::Player *>::iterator it = this->infos_->players.begin() ;
       it != this->infos_->players.end() ; ++it)
    {
      if (*it)
	{
	  (*it)->setClock(&this->_globalClock);
	  Graphic::Vector3f &pos = (*it)->getNowState()->position;
	  (*it)->getGameInfo().map->at(pos.x, pos.z).addCharacter(*it);
	}
    }
}

void	State::Arcade::resetAI()
{
  for (std::list<Character::AI *>::iterator it = this->infos_->AIs.begin() ;
       it != this->infos_->AIs.end() ; ++it)
    {
      (*it)->setClock(&this->_globalClock);
      Graphic::Vector3f &pos = (*it)->getNowState()->position;
      (*it)->getGameInfo().map->at(pos.x, pos.z).addCharacter(*it);
    }
}

void	State::Arcade::resetGameInfo()
{
  if (!this->infos_->bombs.empty())
    this->infos_->bombs.clear();
  if (!this->infos_->explosions.empty())
    this->infos_->explosions.clear();
  this->resetPlayer();
  this->resetAI();
}

void	State::Arcade::bindControllerToPlayer(int playerIndex, int controllerNbr)
{
  Character::Player	*plr = this->infos_->players[playerIndex];

  if (controllerNbr == 1)
    {
      this->_keyBinding[Input::LJ1] = new ActionParam(plr, State::JOYSTIC);
      this->_keyBinding[Input::RJ1] = new ActionParam(plr, State::CAMERA);
      this->_keyBinding[Input::RB1] = new ActionParam(plr, State::SKILL);
      this->_keyBinding[Input::A1] = new ActionParam(plr, State::CLASSICAL_BOMB);
      this->_keyBinding[Input::B1] = new ActionParam(plr, State::SLOT_3);
      this->_keyBinding[Input::X1] = new ActionParam(plr, State::SLOT_1);
      this->_keyBinding[Input::Y1] = new ActionParam(plr, State::SLOT_2);
    }
  else
    {
      this->_keyBinding[Input::LJ2] = new ActionParam(plr, State::JOYSTIC);
      this->_keyBinding[Input::RJ2] = new ActionParam(plr, State::CAMERA);
      this->_keyBinding[Input::RB2] = new ActionParam(plr, State::SKILL);
      this->_keyBinding[Input::A2] = new ActionParam(plr, State::CLASSICAL_BOMB);
      this->_keyBinding[Input::B2] = new ActionParam(plr, State::SLOT_3);
      this->_keyBinding[Input::X2] = new ActionParam(plr, State::SLOT_1);
      this->_keyBinding[Input::Y2] = new ActionParam(plr, State::SLOT_2);
    }
}

void	State::Arcade::resetKeyBinding(Data *datas)
{
  if (!this->_keyBinding.empty())
    this->_keyBinding.clear();

  std::list<Database::Keys *> keys;
  datas->db.getKeys(keys);

  std::map<int, int>	playerControl;
  int	nbr = 1;
  for (int i = 0; i < datas->gameSettings.nbrPlayers; i++)
    {
      int tmp = datas->db.getPlayerController(i);
      playerControl[tmp] = i;
      if (tmp == 2)
	{
	  this->bindControllerToPlayer(i, nbr);
	  nbr++;
	}
    }

  for (std::list<Database::Keys *>::iterator it = keys.begin() ; it != keys.end() ; ++it)
    {
      if (playerControl.find((*it)->id) != playerControl.end())
	{
	  Character::Player *plr = this->infos_->players[playerControl[(*it)->id]];
	  e_ArcadeAction act = static_cast<e_ArcadeAction>((*it)->action);
	  this->_keyBinding[static_cast<Input::Key>((*it)->key)] = new ActionParam(plr, act);
	}
    }
}

//
// INHERITANCES FUNCTIONS
//

void	State::Arcade::draw()
{
  this->_graphic->draw();
}

void	State::Arcade::reset()
{
  Data *datas = Data::getInstance();

  datas->soundManager->stopSound(Sound::MENU_MUSIC);
  datas->soundManager->playSound(Sound::ARCADE_MUSIC);
  this->resetKeyBinding(datas);
  this->resetGameInfo();
  this->_graphic = new Graphic::Graphic(datas->gameSettings.nbrPlayers + 0, *this->infos_);
  this->events_->emptyKey();
  this->_endOfGame = false;
  this->_endOfGameClock.pause();
  this->_endOfGameClock.reset();
  this->_globalClock.reset();
}

//
// UPDATE-RELATED FUNCTIONS
//

void	State::Arcade::updateBombs()
{
  for (std::list<Map::ABomb *>::iterator it = this->infos_->bombs.begin() ;
       it != this->infos_->bombs.end(); ++it)
    {
      if ((*it)->action(0))
	it = this->infos_->bombs.begin();
    }
}

void	State::Arcade::updateExplosions()
{
  for (std::list<Map::Explosion *>::iterator it = this->infos_->explosions.begin() ;
       it != this->infos_->explosions.end(); ++it)
    {
      if ((*it)->isExtinct())
	{
	  std::pair<int, int> const &coord = (*it)->getCoord();
	  this->infos_->map->at(coord.first, coord.second).extinguish();
	  delete *it;
	  this->infos_->explosions.remove(*it);
	  it = this->infos_->explosions.begin();
	}
    }
}

void	State::Arcade::updateKeyBinding()
{
  Data *datas = Data::getInstance();

  while (!this->events_->keyEmpty())
    {
      Input::Event event = this->events_->popKey();
      if ((event.getKeys() == Input::Escape
	   || event.getKeys() == Input::MidleB1
	   || event.getKeys() == Input::MidleB2) && event.getState() == Input::RELEASE)
	{
	  datas->soundManager->stopSound(Sound::ARCADE_MUSIC);
	  datas->soundManager->playSound(Sound::MENU_MUSIC);
	  Data::getInstance()->states->push(State::PAUSE);
	  continue;
	}
      else if (this->_keyBinding.find(event.getKeys()) != this->_keyBinding.end())
	{
	  ActionParam *target = this->_keyBinding[event.getKeys()];
	  target->isPressed = (event.getState() == Input::PRESSED);
	  target->value = event.getValue();
	}
    }
}

void	State::Arcade::playPlayer()
{
  std::vector<bool> playerPlayed(4, false);

  for (std::map<Input::Key, ActionParam *>::iterator it = this->_keyBinding.begin() ;
       it != this->_keyBinding.end() ; ++it)
    {
      if (it->second->isPressed && it->second->player && !it->second->player->isDead())
	{
	  if (it->second->action >= MOVE_UP && it->second->action <= TURN_RIGHT)
	    (this->*(this->_actionMaker)[it->second->action - State::MOVE_UP])(it->second->player);
	  else
	    {
	      it->second->player->action(it->second->action, it->second->value);
	      if (it->second->action != State::JOYSTIC && it->second->action != State::CAMERA)
		it->second->isPressed = false;
	    }
	  playerPlayed[it->second->player->getNbr()] = true;
	}
    }
  for (std::vector<Character::Player *>::iterator it = this->infos_->players.begin() ;
       it != this->infos_->players.end() ; ++it)
    {
      if (*it && !(*it)->isDead())
	{
	  if (playerPlayed.at((*it)->getNbr()) == false)
	    (*it)->action(State::IDLE, 0.0);
	  (*it)->update();
	}
    }
}

void	State::Arcade::updatePlayers()
{
  this->updateKeyBinding();
  this->playPlayer();
}

void	State::Arcade::updateAIs()
{
  for (std::list<Character::AI *>::iterator it = this->infos_->AIs.begin();
       it != this->infos_->AIs.end(); ++it)
    {
      if (!(*it)->isDead())
	{
	  (*it)->calculAction();
	  Character::AI::Action const &todo = (*it)->front();
	  (*it)->action(todo.action, todo.value);
	  (*it)->pop();
	  (*it)->update();
	}
    }
}

void	State::Arcade::isGameFinished()
{
  int	nbrPlayerAlive = 0, nbrAIAlive = 0;

  for (std::vector<Character::Player *>::const_iterator it = this->infos_->players.begin() ;
       it != this->infos_->players.end() ; ++it)
    {
      if (*it && !(*it)->isDead())
	nbrPlayerAlive++;
    }
  for (std::list<Character::AI *>::const_iterator it = this->infos_->AIs.begin() ;
       it != this->infos_->AIs.end() ; ++it)
    {
      if (!(*it)->isDead())
	nbrAIAlive++;
    }
  if (nbrPlayerAlive < 1 || (nbrPlayerAlive == 1 && nbrAIAlive < 1))
    {
      this->_endOfGame = true;
      this->_endOfGameClock.play();
    }
}

void	State::Arcade::update()
{
  Data *datas = Data::getInstance();

  this->updateBombs();
  this->updateExplosions();
  this->updateAIs();
  this->infos_->map->updateMap();
  this->updatePlayers();
  this->_globalClock.reset();
  this->events_->emptyMouse();
  if (!this->_endOfGame)
    this->isGameFinished();
  this->_endOfGameClock.update();
  if (this->_endOfGame && this->_endOfGameClock.getTotalElapsedTime() > 3.0)
    {
      datas->soundManager->stopSound(Sound::ARCADE_MUSIC);
      datas->soundManager->playSound(Sound::MENU_MUSIC);
      datas->states->push(State::SCORE);
    }
}

void	State::Arcade::reload()
{
  Data *datas = Data::getInstance();

  for (std::map<Input::Key, ActionParam *>::iterator it = this->_keyBinding.begin() ;
       it != this->_keyBinding.end() ; ++it)
    it->second->isPressed = false;
  datas->soundManager->playSound(Sound::ARCADE_MUSIC);
  datas->soundManager->stopSound(Sound::MENU_MUSIC);
  this->_globalClock.reset();
}

//
// PRIVATE FUNCTIONS
//

Input::e_eventState State::Arcade::getEventState(e_ArcadeAction action) const
{
  return (action < IDLE ? Input::PRESSED : Input::RELEASE);
}

void	State::Arcade::move_up(Character::Player *player)
{
  player->action(State::MOVE, MOVE_VALUE);
}

void	State::Arcade::move_down(Character::Player *player)
{
  player->action(State::MOVE, -MOVE_VALUE);
}

void	State::Arcade::turn_left(Character::Player *player)
{
  player->action(State::TURN, TURN_VALUE);
}

void	State::Arcade::turn_right(Character::Player *player)
{
  player->action(State::TURN, -TURN_VALUE);
}

//
// PUBLIC FUNCTIONS
//

int	State::Arcade::calcDmg(Statistics const &attacker, Statistics const &defender)
{
  float multiple = 1.0;
  if (rand() % 100 < (attacker.get(Statistics::CRITICAL)
		      - defender.get(Statistics::RESILIENCE)))
    multiple = 1.5;
  int damages = attacker.get(Statistics::POWER) * multiple;
  damages = (damages / 10) + damages;
  int res = damages - defender.get(Statistics::DEFENSE);
  return (res < (damages / 10) ? (damages / 10) : res);
}
