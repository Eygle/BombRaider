#ifndef __GAMEMENUNEXT__
#define __GAMEMENUNEXT__

#include "GameMenu.hpp" // GameMenu
#include "AButton.hpp" // AButton
#include "Data.hpp" // Data

namespace Menu
{
  class GameMenuNext : public AButton 
  {
  private :
    GameMenu	*state_;
    Data	*data_;
  public :
    GameMenuNext(GameMenu	*state);
    ~GameMenuNext();
    virtual void action(char c);
    virtual void update();
  };
};

#endif
