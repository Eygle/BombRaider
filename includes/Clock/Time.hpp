#ifndef	__TIME_HPP__
#define __TIME_HPP__

#include <sys/time.h> 
#include <unistd.h>

class	Time
{
private:
  struct	timeval now_;
public:
  Time();
  ~Time();
public:
  int		getTimeS();
  int		getTimeUS();
};

#endif
