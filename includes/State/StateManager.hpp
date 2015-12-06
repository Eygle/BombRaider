#ifndef __STATE_MANAGER_HPP__
# define __STATE_MANAGER_HPP__

#include <stack>
#include <map>

#include "AState.hpp"

namespace State
{
  class StateManager
  {
    std::map<e_State, AState *>		statePool_;
    std::stack<AState *>		stateStack_;
    GameInfo				*info_;
  public:
    StateManager();
    ~StateManager();

    void	push(e_State state);
    void	popTo(e_State state);
    void	pop();
    bool	update();
    void	draw();
    void	init(Input::EventManager *, GameInfo *, gdl::GameClock *);
    void	backToMenu();
  };
};
#endif
