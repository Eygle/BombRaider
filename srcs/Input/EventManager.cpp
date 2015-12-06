#include "Input/EventManager.hpp"

namespace Input
{
  EventManager::EventManager()
  {
  }

  EventManager::~EventManager()
  {
  }

  void	EventManager::pushKey(Event &event)
  {
    this->mutex_.lock();
    this->keyboardEvents_.push_back(event);
    this->mutex_.unlock();
  }

  void	EventManager::pushMouse(s_mouseEvent &input)
  {
    this->mutex_.lock();
    this->mouseEvents_.push_back(input);
    this->mutex_.unlock();
  }

  Event	 EventManager::popKey()
  {
    Event 	tmp;

    this->mutex_.lock();
    if (this->keyboardEvents_.empty())
      return (tmp);
    else
      {
	tmp = this->keyboardEvents_.front();
	this->keyboardEvents_.pop_front();
      }
    this->mutex_.unlock();
    return (tmp);
  }

  s_mouseEvent	EventManager::popMouse()
  {
    s_mouseEvent				tmp;

    this->mutex_.lock();
    if (this->mouseEvents_.empty())
      return (tmp);
    else
      {
	tmp = this->mouseEvents_.front();
	this->mouseEvents_.pop_front();
      }
    this->mutex_.unlock();
    return (tmp);
  }

  void		EventManager::pushKeyList(std::list<Event> &events)
  {
    this->mutex_.lock();
    this->keyboardEvents_.insert(keyboardEvents_.end(), events.begin(), events.end());
    this->mutex_.unlock();
  }

   void		EventManager::pushButtonList(std::list<s_mouseEvent> &events)
  {
    this->mutex_.lock();
    this->mouseEvents_.insert(mouseEvents_.end(), events.begin(), events.end());
    this->mutex_.unlock();
  }

  bool	EventManager::keyEmpty()
  {
    bool result;

    this->mutex_.lock();
    result = this->keyboardEvents_.empty();
    this->mutex_.unlock();
    return (result);
  }

  bool	EventManager::mouseEmpty()
  {
    bool result;

    this->mutex_.lock();
    result = this->mouseEvents_.empty();
    this->mutex_.unlock();
    return (result);
  }

  void		EventManager::emptyKey()
  {
    this->mutex_.lock();
    this->keyboardEvents_.clear();
    this->mutex_.unlock();
  }

  void		EventManager::emptyMouse()
  {
    this->mutex_.lock();
    this->mouseEvents_.clear();
    this->mutex_.unlock();
  }
}
