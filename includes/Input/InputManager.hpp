#ifndef  __INPUTMANAGER__
#define  __INPUTMANAGER_

#include <GDL/Input.hpp>
#include "EventManager.hpp"
#include "EventHandler.hpp"
#include "MouseHandler.hpp"

namespace Input
{
  class InputManager
  {
  private:
    EventManager		*eventManager_;
    EventHandler		eventHandler_;
    MouseHandler		mouseHandler_;
    gdl::Input			*input_;
  public:
    InputManager(EventManager *event, gdl::Input *input);
    ~InputManager();

    void	update();
    bool	addPad();
    void	removePad();

    static int ManageInput(Input::InputManager *inputs);
  };
};

#endif
