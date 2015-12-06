#ifndef __MAINMENU__
#define __MAINMENU__

#include "MenuState.hpp"
#include "Graphic/GuiImage.hpp" // BG
# include "Menu/LoadButton.hpp"

namespace Menu
{
  class MainMenu : public MenuState
  {
  public:
    MainMenu();
    virtual ~MainMenu();
    virtual void update();
    virtual void draw();
    void	init();

  private:
    LoadButton	*loadButton_;

  };
};

#endif
