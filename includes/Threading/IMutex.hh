#ifndef __IMUTEX__
#define __IMUTEX__

namespace Threading
{
  class IMutex 
  {
  public:
    virtual ~IMutex(){};
    virtual void lock() = 0;
    virtual void unlock() = 0;
    virtual bool tryLock() = 0;
  };
};
#endif 
