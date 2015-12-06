#ifndef __MUTEX__
#define __MUTEX__

#include <pthread.h>

#include "IMutex.hh"
namespace Threading
{
  class Mutex : public IMutex
  {
  private:
    pthread_mutex_t	mutex_;

  public :  
    //CTOR
    Mutex();
    //DTOR
    virtual ~Mutex();
  
    // Function 
    virtual void lock();
    virtual void unlock();
    virtual bool tryLock();
  };
}
#endif 
