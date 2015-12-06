#ifndef __GAMEMENU__
#define  __GAMEMENU__

#include <list>
#include "MenuState.hpp"
#include "ProfilInput.hpp"
#include "Switcher.hpp"

namespace Menu
{
  class GameMenu :  public MenuState
  {
  private :
    Graphic::GuiImage			layout_;
    std::list<Switcher *>		switchers_;
    Switcher *				switcherFocus_;
    std::list<ProfilInput *>		profil_;
    ProfilInput *			profilFocus_;
    ProfilInput *			profilLastFocus_;
    unsigned int			*nbPlayer_;
    
    void		drawSwitcher();
    void		drawProfil();
    Switcher		*findSwitcher(int x, int y);
    ProfilInput		*findInput(int x, int y);
    void		updateInput();
    void		updateSwitcher();

  public :
    GameMenu();
    ~GameMenu();
    
    virtual void update();
    virtual void draw();
    virtual void reset();
    
    void		initSwitcher(std::list<Switcher *> &switcher);
    void		initProfilInput(std::list<ProfilInput *> &input);
    void		saveValue();
    void		init();
  };
};
#endif 
