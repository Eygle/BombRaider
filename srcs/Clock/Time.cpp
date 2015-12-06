#include <string>
#include "Clock/Time.hpp"

Time::Time()
{
  gettimeofday(&this->now_, 0);
}

Time::~Time()
{}

int		Time::getTimeS()
{
  gettimeofday(&this->now_, 0);
  return (this->now_.tv_sec);
}

int		Time::getTimeUS()
{
  gettimeofday(&this->now_, 0);
  return ((this->now_.tv_sec * 1000000) + this->now_.tv_usec);
}
