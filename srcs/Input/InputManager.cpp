#include <unistd.h>

#include <list>

#include "Input/InputManager.hpp"

namespace Input
{
  InputManager::InputManager(EventManager *event, gdl::Input *input)
    : eventManager_(event), eventHandler_(input), mouseHandler_(input), input_(input)
  {
  }

  InputManager::~InputManager()
  {
    this->eventHandler_.removePad();
  }

  void	InputManager::update()
  {

    std::list<Event> tmp = this->eventHandler_.update();
    std::list<s_mouseEvent> tmpMouse = this->mouseHandler_.update();
    this->eventManager_->pushKeyList(tmp);
    this->eventManager_->pushButtonList(tmpMouse);
  }

  bool	InputManager::addPad()
  {
    return (this->eventHandler_.addPad());
  }

  void	InputManager::removePad()
  {
    this->eventHandler_.removePad();
  }

  int InputManager::ManageInput(Input::InputManager *inputs)
  {
    while (true)
      {
	inputs->update();
	usleep(50);
      }
    return (0);
  }
}
