#ifndef __THREAD__
#define __THREAD__

#include <pthread.h>

#include "IThread.hh"

namespace Threading
{
  template <class T, class U> class Thread : public IThread
  {
    typedef T (*funcPtr)(U);
    funcPtr	ptr_;
    pthread_t	thread_;
    T		res_;
    U		param_;

  public:
    // CTOR
    Thread(funcPtr ptr, U param)
      : ptr_(ptr), param_(param)
    {};

    // DTOR
    ~Thread(){};

    // Function
    void	wait()
    {
      void	**res = 0;

      pthread_join(this->thread_, res);
      this->res_ = *(reinterpret_cast<T *>(*res));
    }

    void	create()
    {
      pthread_create(&(this->thread_), 0, reinterpret_cast<void *(*)(void *)>(this->ptr_),
		     reinterpret_cast<void *>(this->param_));
    }

    T		getRes()
    {
      return (this->res_);
    }

    void	cancel()
    {
      pthread_cancel(this->thread_);
    }
  };
};
#endif
