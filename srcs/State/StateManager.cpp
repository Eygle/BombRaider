#include "State/StateManager.hpp"
#include "Menu/MainMenu.hpp"
#include "Menu/GameMenu.hpp"
#include "Menu/SettingState.hpp"
#include "Menu/SelectPlayer.hpp"
#include "Menu/PauseState.hpp"
#include "Menu/Binding/Binding.hpp"
#include "Menu/ScoreState.hpp"
#include "Menu/CreditState.hpp"
#include "Menu/IntroState.hpp"
#include "State/Arcade.hpp"
#include "Data.hpp"
#include "Character/AI.hpp"
#include "Character/Player.hpp"

namespace State
{
  StateManager::StateManager()
  {
    Data *data = Data::getInstance();

    data->states = this;
    this->statePool_[MAINMENU] = new Menu::MainMenu;
    this->statePool_[ARCADE] = new State::Arcade;
    this->statePool_[SETTING] = new Menu::SettingState;
    this->statePool_[PAUSE] = new Menu::PauseState;
    this->statePool_[BINDING] = new Menu::Binding;
    this->statePool_[GAMEMENU] = new Menu::GameMenu;
    this->statePool_[SCORE] = new Menu::ScoreState(true);
    this->statePool_[RANKING] = new Menu::ScoreState(false);
    this->statePool_[CREDITS] = new Menu::CreditState;
    this->statePool_[SELECTPLAYER1] = new Menu::SelectPlayer(SELECTPLAYER1);
    this->statePool_[SELECTPLAYER2] = new Menu::SelectPlayer(SELECTPLAYER2);
    this->statePool_[SELECTPLAYER3] = new Menu::SelectPlayer(SELECTPLAYER3);
    this->statePool_[SELECTPLAYER4] = new Menu::SelectPlayer(SELECTPLAYER4);
    this->statePool_[INTRO] = new Menu::IntroState;
  }

  StateManager::~StateManager()
  {
    delete this->statePool_[MAINMENU];
    delete this->statePool_[ARCADE];
    delete this->statePool_[SETTING];
    delete this->statePool_[PAUSE];
    delete this->statePool_[SCORE];
    delete this->statePool_[SELECTPLAYER1];
    delete this->statePool_[SELECTPLAYER2];
    delete this->statePool_[SELECTPLAYER3];
    delete this->statePool_[SELECTPLAYER4];
    delete this->statePool_[BINDING];
    delete this->statePool_[CREDITS];
    delete this->statePool_[INTRO];
  }

  void	StateManager::push(e_State state)
  {
    this->stateStack_.push(this->statePool_[state]);
    this->statePool_[state]->reset();
  }

  void	StateManager::popTo(e_State state)
  {
    AState *target = this->statePool_[state];

    while (this->stateStack_.top() != target)
      this->stateStack_.pop();
    target->reload();
  }

  void	StateManager::pop()
  {
    this->stateStack_.pop();
    if (!this->stateStack_.empty())
      this->stateStack_.top()->reload();
  }


  bool	StateManager::update()
  {
    if (this->stateStack_.empty())
      return (false);
    this->stateStack_.top()->update();
    return (true);
  }

  void	StateManager::draw()
  {
    if (!this->stateStack_.empty())
      this->stateStack_.top()->draw();
  }

  void StateManager::init(Input::EventManager *events,
			  GameInfo *infos, gdl::GameClock *clock)
  {
    this->info_ = infos;
    for (int state = static_cast<int>(ARCADE) ; state != static_cast<int>(LAST) ; ++state)
      {
	AState *targetState = this->statePool_[static_cast<e_State>(state)];
	targetState->setEventManager(events);
	targetState->setInfos(infos);
	targetState->setClock(clock);
      }
    dynamic_cast<Menu::GameMenu *>(this->statePool_[GAMEMENU])->init();
    dynamic_cast<Menu::PauseState *>(this->statePool_[PAUSE])->init();
    dynamic_cast<Menu::MainMenu *>(this->statePool_[MAINMENU])->init();
  }

  void StateManager::backToMenu()
  {
    {
    std::vector<Character::Player *>::iterator it = this->info_->players.begin();
    std::vector<Character::Player *>::iterator end = this->info_->players.end();

    while (it != end)
      {
	if (*it)
	  {
	    delete (*it);
	    *it = 0;
	  }
	++it;
      }
    }
    {
      std::list<Character::AI *>::iterator	it = this->info_->AIs.begin();
      std::list<Character::AI *>::iterator	end = this->info_->AIs.end();
      while (it != end)
	{
	  if (*it)
	    delete (*it);
	  ++it;
	}
      this->info_->AIs.clear();
      this->popTo(State::MAINMENU);
    }
  }
}
