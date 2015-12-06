#include "Input/EventHandler.hpp"

static int	updatePad(Input::Pad *pad)
{
  while (true)
    pad->update();  	  
  return (0);
}

namespace Input
{
  EventHandler::EventHandler(gdl::Input *input):
    nbpad_(0), pad1_(0), pad2_(0)
  {
    int	i = 0;
    this->pad_[0] = new Pad(1, &(this->event_), &(this->mutex_));
    this->pad_[1] = new Pad(2, &(this->event_), &(this->mutex_));
    this->input_ = input;
    while (i < gdl::Keys::Count)
      {
	(this->keypressed_[static_cast<Key>(i)]) = false;
	i++;
      }
  }

  EventHandler::~EventHandler()
  {
    this->removePad();
  }

  std::list<Event> EventHandler::update()
  {
    int				i = 0;
    std::list<Event>		result;
    while (i < gdl::Keys::Count)
      {
	if (this->input_->isKeyDown(static_cast<gdl::Keys::Key>(i)))
	  {
	    if (!this->keypressed_[static_cast<Key>(i)])
	      {
		this->keypressed_[static_cast<Key>(i)] = true;
		Event event(static_cast<Key>(i),PRESSED, 32000);
		result.push_back(event);
	      }
	  }
	else if (this->keypressed_[static_cast<Key>(i)] == true)
	  {
	    this->keypressed_[static_cast<Key>(i)] = false;
	    Event event(static_cast<Key>(i),RELEASE, 32000);
	    result.push_back(event);
	  }
	i++;
      }
  
    this->mutex_.lock();
    if (!this->event_.empty())
      {
	result.insert(result.end(),this->event_.begin(), this->event_.end());
	this->event_.clear();
      }
    this->mutex_.unlock();
    return (result);
  }

  bool EventHandler::addPad()
  {
    if (this->nbpad_ == 2)
      {
	return (false);
      }
    else
      {
	if (!((this->pad_)[this->nbpad_])->init())
	  return (false);
	this->nbpad_++;
	if (this->nbpad_ == 1)
	  {
	    this->pad1_ = new Threading::Thread<int, Pad *>(&(updatePad), this->pad_[0]);
	    this->pad1_->create();
	  }
	else
	  {
	    this->pad2_ = new Threading::Thread<int, Pad *>(&(updatePad), this->pad_[1]);
	    this->pad2_->create();
	  }
	return (true);
      }
  }
  
  void	EventHandler::removePad()
  {
    if (this->pad1_)
      {

	this->pad1_->cancel();
	delete this->pad1_;
	this->pad1_ = 0;
	this->pad_[0]->stop();

      }
    if (this->pad2_)
      {
	this->pad2_->cancel();
	delete this->pad2_;
	this->pad2_ = 0;
	this->pad_[1]->stop();
      }
  }
  
}
