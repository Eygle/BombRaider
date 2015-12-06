#ifndef __ITHREAD__
#define __ITHREAD__

#include <pthread.h>

namespace Threading
{
  class IThread
  {
  public :
    virtual		~IThread(){};
    virtual void		wait() = 0 ;

  };
};
#endif
