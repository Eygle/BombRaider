#ifndef CORE_H_
# define CORE_H_

# include "GameInfo.hpp"
# include "Input/EventManager.hpp"
# include "Input/InputManager.hpp"
# include "State/StateManager.hpp"
# include "GDL/Game.hpp"
# include "Threading/Thread.hpp"
# include "Data.hpp"

class Core : public gdl::Game
{
public:
  Core();
  ~Core();

  void	initialize();
  void	draw();
  void	unload();
  void	update();

private:
  GameInfo		gameInfos_;
  Input::EventManager	eventManager_;
  State::StateManager	stateManager_;
  Input::InputManager	inputManager_;
  Threading::Thread<int, Input::InputManager *>	*thread_;

  Core(Core const &);
  Core &operator=(Core const &);
};

#endif
