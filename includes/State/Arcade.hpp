#ifndef ARCADE_H_
# define ARCADE_H_

# include "GDL/Clock.hpp"

# include "State/AState.hpp"
# include "Statistics.hpp"
# include "Graphic/Graphic.hpp"
# include "Input/Event.hpp"
# include "GameInfo.hpp"
# include "State/StateActions.hpp"
# include "Clock/Clock.hpp"
# include "Data.hpp"

# define TURN_VALUE	1.0
# define MOVE_VALUE	1.0

namespace Graphic
{
  class Graphic;
}

namespace Character
{
  class Player;
}

class GameInfo;

namespace State
{
  class Arcade : public AState
  {
    typedef void (State::Arcade::*ActionFunc)(Character::Player *);

    struct ActionParam
    {
      bool		isPressed;
      Character::Player *player;
      e_ArcadeAction	action;
      float		value;

      ActionParam(Character::Player *, e_ArcadeAction);
      ~ActionParam();

    private:
      ActionParam();
    };

    Graphic::Graphic			*_graphic;
    Clock				_globalClock;
    ActionFunc				_actionMaker[4];
    std::map<Input::Key, ActionParam *>	_keyBinding;
    gdl::Clock				_endOfGameClock;
    bool				_endOfGame;

    void	resetGameInfo();
    void	bindControllerToPlayer(int, int);
    void	resetKeyBinding(Data *datas);

    void	updateBombs();
    void	updateExplosions();
    void	updateKeyBinding();
    void	playPlayer();
    void	updatePlayers();
    void	updateAIs();
    void	isGameFinished();

    void	resetPlayer();
    void	resetAI();

    void	move_up(Character::Player *player);
    void	move_down(Character::Player *player);
    void	turn_left(Character::Player *player);
    void	turn_right(Character::Player *player);

    Input::e_eventState	getEventState(e_ArcadeAction) const;

    Arcade(Arcade const &);
    Arcade &operator=(Arcade const &);

  public:
    Arcade();
    ~Arcade();

    void	update();
    void	reset();
    void	draw();
    void	reload();

    static int calcDmg(Statistics const &attacker, Statistics const &defender);
  };
};
#endif
