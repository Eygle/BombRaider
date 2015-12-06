#ifndef __ICHARACTER_HPP__
#define __ICHARACTER_HPP__

#include "State/StateActions.hpp"
#include "GameInfo.hpp"

class GameInfo;

namespace Character
{
  class ICharacter
  {
  public:
    virtual ~ICharacter(){}
    virtual void		action(State::e_ArcadeAction action, float) = 0;
  };
};

#endif
