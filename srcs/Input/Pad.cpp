#include <cmath>

#include "Input/Pad.hpp"

namespace Input
{
  // CTOR
  Pad::Pad(int id, std::list<Event> *event, Threading::Mutex *mut) :
    id_(id), event_(event), mut_(mut)
  {
    this->buttonmap_[0] = static_cast<Key>(A1 + (id - 1) * 16);
    this->buttonmap_[1] = static_cast<Key>(B1 + (id - 1) * 16);
    this->buttonmap_[2] = static_cast<Key>(X1 + (id - 1) * 16);
    this->buttonmap_[3] = static_cast<Key>(Y1 + (id - 1) * 16);
    this->buttonmap_[4] = static_cast<Key>(LB1 + (id - 1) * 16);
    this->buttonmap_[5] = static_cast<Key>(RB1 + (id - 1) * 16);
    this->buttonmap_[6] = static_cast<Key>(Back1 + (id - 1) * 16);
    this->buttonmap_[7] = static_cast<Key>(Start1 + (id - 1) * 16);
    this->buttonmap_[8] = static_cast<Key>(MidleB1 + (id - 1) * 16);
    this->buttonmap_[9] = static_cast<Key>(LJP1 + (id - 1) * 16);
    this->buttonmap_[10] = static_cast<Key>(RJP1 + (id - 1) * 16);
  }

  // DTOR
  Pad::~Pad()
  {
    if (this->file_.is_open())
      this->file_.close();
  }

  // GETTER
  int  Pad::getId() const
  {
    return (this->id_);
  }

  bool Pad::init()
  {
    if (this->id_ == 1)
      {
	this->file_.open("/dev/input/js1", std::fstream::in);
	return (this->file_.is_open());
      }
    else
      {
	this->file_.open("/dev/input/js2", std::fstream::in);
	return (this->file_.is_open());
      }
  }

  void		Pad::manageJ1(const js_event &js, std::list<Event> &event)
  {
    if (this->j1_.curent == -1)
      {
	this->j1_.curent = js.number;
	if (js.number == 1)
	  this->j1_.val2 = js.value;
	else
	  this->j1_.val1 = js.value;
      }
    else
      {
	if (js.number == 1)
	  this->j1_.val2 = js.value;
	else
	  this->j1_.val1 = js.value;
	Event	tmp =  calcJoy(this->j1_);
	if (tmp.getValue() > 0)
	  {
	    tmp.setKeys(static_cast<Key>((this->id_- 1) * 16 +  LJ1));
	    event.push_back(tmp);
	  }
	this->j1_.curent = -1;
      }
  }

  void		Pad::manageJ2(const js_event &js, std::list<Event> &event)
  {
    if (this->j2_.curent == -1)
      {
	this->j2_.curent = js.number;
	if (js.number == 4)
	  this->j2_.val2 = js.value;
	else
	  this->j2_.val1 = js.value;
      }
    else
      {
	if (js.number == 4)
	  this->j2_.val2 = js.value;
	else
	  this->j2_.val1 = js.value;
	Event	tmp =  calcJoy(this->j2_);
	if (tmp.getValue() > 0)
	  {
	    tmp.setKeys(static_cast<Key>((this->id_- 1) * 16 +  RJ1));
	    event.push_back(tmp);
	  }
	this->j2_.curent = -1;
      }
  }


  Event		Pad::calcJoy(const Joystick   &joy)
  {
    Event	result;
    result.setValue(1);
    if (std::abs(joy.val1) > PRECISIONPAD || std::abs(joy.val2) > PRECISIONPAD)
      {
	double op;
	double adj;
	double angle = 0.0;
	if (joy.val2 > 0)
	  angle += 180;
	if ((joy.val2 >= 0 && joy.val1 >= 0) || (joy.val2 < 0 && joy.val1 < 0))
	  {
	    angle += 90;
	    adj = joy.val2;
	    op = joy.val1;
	  }
	else
	  {
	    adj = joy.val1;
	    op = joy.val2;
	  }
	if (adj != 0)
	  {
	    angle += std::atan(std::abs(op)/std::abs(adj)) * 180/3.14;
	    result.setValue(angle);
	  }
	result.setState(PRESSED);
      }
    else
      result.setState(RELEASE);
    return (result);
  }

  void		Pad::update()
  {
    js_event	js;
    std::list<Event> result;
    if (this->file_.is_open())
      {
	this->file_.read((char *)&js ,sizeof(js_event));
	if (js.type == JS_EVENT_BUTTON)
	  {
	    Event  event(this->buttonmap_[js.number],static_cast<e_eventState>(js.value), js.value);
	    result.push_back(event);
	  }
	else if (js.type == JS_EVENT_AXIS)
	  {
	    if (js.number == 1 || js.number == 0)
	      manageJ1(js,result);
	    if (js.number == 3 || js.number == 4)
	      manageJ2(js,result);
	  }
	if (!result.empty())
	  {
	    this->mut_->lock();
	    this->event_->insert(this->event_->end(), result.begin(), result.end());
	    this->mut_->unlock();
	  }
      }
  }

  void		Pad::stop()
  {
    if (this->file_.is_open())
      this->file_.close();
  }

}
