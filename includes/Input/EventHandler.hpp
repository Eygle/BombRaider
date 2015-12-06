#ifndef __EVENTHANDLER__
#define __EVENTHANDLER__

#include <map>
#include <list>

#include "Threading/Mutex.hpp"
#include "Threading/Thread.hpp"
#include "Event.hpp"
#include "Pad.hpp"

namespace Input
{
  class EventHandler
  {
  private :
    std::map<Key, bool>			keypressed_;
    gdl::Input				*input_;
    int					nbpad_;
    Pad					*pad_[2];
    std::list<Event>			event_;
    Threading::Mutex			mutex_;
    Threading::Thread<int, Pad *>	*pad1_;
    Threading::Thread<int, Pad *>	*pad2_;
  public :
    EventHandler(gdl::Input *input);
    ~EventHandler();
    
    std::list<Event>	update();
    bool		addPad();
    void		removePad();
  };
};
#endif
