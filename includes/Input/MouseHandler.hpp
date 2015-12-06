#ifndef __MOUSEHANDLER__
#define __MOUSEHANDLER__

#include <map>
#include <list>
#include <utility>

#include <GDL/Input.hpp>

#include "Event.hpp"

namespace Input
{
  struct s_mouseEvent
  {
    e_eventState	       	mouseState;
    gdl::Mouse::Button		clic;
    std::pair<int, int>		pos;

    //CTOR
    s_mouseEvent(gdl::Mouse::Button button,e_eventState stat, int x, int y);
    s_mouseEvent();
  };

  class MouseHandler 
  {
  private: 
    std::map<gdl::Mouse::Button, bool>			buttonPressed_;
    gdl::Input						*input_;
    
  public :
    MouseHandler(gdl::Input *input);
    ~MouseHandler();
    
    std::list<s_mouseEvent>	update();
  };
};


#endif 
