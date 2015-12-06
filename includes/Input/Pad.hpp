#ifndef __PAD__
#define __PAD__

#include <list>
#include <map>
#include <fstream>
#include <linux/joystick.h>

#include "Threading/Mutex.hpp"
#include "EventManager.hpp"
#include "Event.hpp"

#define PRECISIONPAD  10000

namespace Input
{
  struct Joystick 
  {
    int	curent;
    int val1;
    int val2;
  };

  class Pad
  {
  private:
    int				id_;
    std::fstream		file_;
    std::map<char, Key>		buttonmap_;
    Joystick			j1_;
    Joystick			j2_;
    std::list<Event>		*event_;
    Threading::Mutex		*mut_;
  public:
    // CTOR
    Pad(int id, std::list<Event> *event, Threading::Mutex  *mut);

    // DTOR
    ~Pad();

    //GETTER
    int		getId() const; 
    
    // Function
    bool		init();
    void		update();
    void		stop();
  private :
    Event	calcJoy(const Joystick   &joy);
    void	manageJ1(const js_event &js, std::list<Event> &event);
    void	manageJ2(const js_event &js, std::list<Event> &event);
    
  };
};

#endif 
