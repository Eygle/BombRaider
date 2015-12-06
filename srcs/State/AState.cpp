#include "State/AState.hpp"

namespace State
{
  void	AState::setEventManager(Input::EventManager *event)
  {
    this->events_ = event;
  }

  void  AState::setClock(gdl::GameClock *clock)
  {
    this->clock_ = clock;
  }

  void	AState::setInfos(GameInfo *infos)
  {
    this->infos_ = infos;
  }

  e_State	AState::getType() const
  {
    return (this->type_);
  }

  void	AState::reload()
  {
  }
}
