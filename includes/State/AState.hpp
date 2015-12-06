#ifndef __ASTATE__
#define __ASTATE__

#include "GameInfo.hpp"
#include "GDL/GameClock.hpp"
#include "Input/EventManager.hpp"

namespace State
{
  enum e_State
    {
      ARCADE,
      MAINMENU,
      GAMEMENU,
      SETTING,
      BINDING,
      SELECTPLAYER1,
      SELECTPLAYER2,
      SELECTPLAYER3,
      SELECTPLAYER4,
      PAUSE,
      SCORE,
      RANKING,
      CREDITS,
      INTRO,
      LAST,
    };

  class AState
  {
  protected :
    Input::EventManager	*events_;
    GameInfo		*infos_;
    gdl::GameClock	*clock_;
    e_State		type_;

  public :
    virtual ~AState() {};
    virtual void draw() = 0;
    virtual void reset() = 0;
    virtual void update() = 0;

    // SETTER
    void	setEventManager(Input::EventManager *);
    void	setInfos(GameInfo *);
    void	setClock(gdl::GameClock *);

    // GETTER
    e_State	getType() const;

    virtual void	reload();
  };
}
#endif
