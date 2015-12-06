#include "Input/MouseHandler.hpp"

namespace Input
{
  // s_mouseEvent

  s_mouseEvent::s_mouseEvent()
  {
  }

  s_mouseEvent::s_mouseEvent(gdl::Mouse::Button button, e_eventState stat, int x, int y)
    :  mouseState(stat), clic(button), pos(x,y)
  {
  }

  // CTOR
  MouseHandler::MouseHandler(gdl::Input *input)
    : input_(input)
  {
    int		i = 0;
    while (i <= gdl::Mouse::Middle)
      {
	this->buttonPressed_[static_cast<gdl::Mouse::Button>(i)] = false;
	i++;
      }
  }

  // DTOR
  MouseHandler::~MouseHandler()
  {
  }

  std::list<s_mouseEvent> MouseHandler::update()
  {
    int		i = 0;

    std::list<s_mouseEvent>		result;
    while (i < gdl::Mouse::Middle)
      {
	if (this->input_->isMouseButtonDown(static_cast<gdl::Mouse::Button>(i)))
	  {
	    this->buttonPressed_[static_cast<gdl::Mouse::Button>(i)] = true;
	    s_mouseEvent event(static_cast<gdl::Mouse::Button>(i), PRESSED,
			       this->input_->getMousePositionX(),
			       this->input_->getMousePositionY());
	    result.push_back(event);
	  }
	else if (this->buttonPressed_[static_cast<gdl::Mouse::Button>(i)] == true)
	  {
	    this->buttonPressed_[static_cast<gdl::Mouse::Button>(i)] = false;
	    s_mouseEvent event(static_cast<gdl::Mouse::Button>(i) , RELEASE,
			       this->input_->getMousePositionX(),
			       this->input_->getMousePositionY());
	    result.push_back(event);
	  }
	else
	  {
	     s_mouseEvent event(static_cast<gdl::Mouse::Button>(i) , NOTHING,
			       this->input_->getMousePositionX(),
			       this->input_->getMousePositionY());
	    result.push_back(event);
	  }
	i++;
      }
    return (result);
  }
}
