#include "Clock/Clock.hpp"

Clock::Clock()
{
  this->startClock_ = this->time_.getTimeUS();
}

Clock::~Clock()
{}

float		Clock::getElapsedTime()
{
  return ((this->time_.getTimeUS() - this->startClock_) / 1000000.0);
}

void		Clock::reset()
{
  this->startClock_ = this->time_.getTimeUS();
}
