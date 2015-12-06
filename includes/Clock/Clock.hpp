#ifndef	__CLOCK_HPP__
#define __CLOCK_HPP__

#include "Time.hpp"

class	Clock
{
private:
  Time		time_;
  int		startClock_;
public:
  Clock();
  ~Clock();
public:
  void		reset();
  float		getElapsedTime();
};

#endif
