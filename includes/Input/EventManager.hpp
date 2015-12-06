#ifndef __EVENTMANAGER__
# define __EVENTMANAGER__

#include <list>
#include <utility>
#include <GDL/Input.hpp>

#include "../Threading/Mutex.hpp"
#include "Event.hpp"
#include "MouseHandler.hpp"

typedef void Player ;

namespace Input
{
  class EventManager
  {
  protected:
    Threading::Mutex		mutex_;
    std::list<Event>		keyboardEvents_;
    std::list<s_mouseEvent>	mouseEvents_;

  public:
    EventManager();
    ~EventManager();

    void		pushKey(Event &event);
    void		pushKeyList(std::list<Event> &events);
    void		pushMouse(s_mouseEvent &input);
    void		pushButtonList(std::list<s_mouseEvent> &events);

    Event		popKey();
    s_mouseEvent	popMouse();

    bool		mouseEmpty();
    bool		keyEmpty();
    
    void		emptyKey();
    void		emptyMouse();
  };
};

#endif
