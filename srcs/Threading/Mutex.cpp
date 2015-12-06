#include "Threading/Mutex.hpp"
namespace Threading
{
  //CTOR
  Mutex::Mutex()
  {
    pthread_mutex_init(&(this->mutex_), 0);
  }
  //DTOR
  Mutex::~Mutex()
  {
  }
  // Function
  void Mutex::lock()
  {
    pthread_mutex_lock(&(this->mutex_));
  }

  void Mutex::unlock()
  {
    pthread_mutex_unlock(&(this->mutex_));
  }

  bool Mutex::tryLock()
  {
    if (pthread_mutex_trylock(&(this->mutex_)))
      return (false);
    return (true);
  }
}
