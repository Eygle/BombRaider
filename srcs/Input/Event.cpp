
#include "Input/Event.hpp"

namespace Input
{
  Event::Event() :
  key_(NONE)
  {
  }
  
  Event::Event(Key key, e_eventState state, float value) :
    key_(key), state_(state), value_(value)
  {
  }
  
  Event::~Event()
  {
  }
  
  Key Event::getKeys() const
  {
    return (this->key_);
  }

  e_eventState   Event::getState() const
  {
    return (this->state_);
  }

  int		 Event::getValue() const
  {
    return (this->value_);
  }
  
  void		Event::setKeys(Key key)
  {
    this->key_ = key;
  }
  void		Event::setState(e_eventState state)
  {
    this->state_ = state;
  }
  void		Event::setValue(float value)
  {
    this->value_ = value;
  }
}
