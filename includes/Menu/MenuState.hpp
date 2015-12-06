#ifndef __MENUSTATE__
#define __MENUSTATE__

#include <list>
#include <GDL/Text.hpp>

#include "../State/AState.hpp" // Heritage

#include "../Graphic/GuiImage.hpp" // BG

#include "AButton.hpp" //  Boutton
#include "MenuCamera.hpp" // Camera


namespace Menu
{
  class MenuState : public State::AState
  {
  protected :
    std::list<AButton *>		buttons_;
    std::list<AButton *>::iterator	focus_;
    MenuCamera				camera_;
    Graphic::GuiImage			background_;
  public :
    // CTOR
    MenuState();
    // DTOR
    virtual ~MenuState();

    // METHODE
    virtual void	draw();
    virtual void	update();
    virtual void	reset();

    // SETTER
    void	setBackground(Data::e_image bg);
    std::list<AButton *>::iterator     findButtons(int x, int y);
    void	nextButton();
    void	prevButton();
    void	drawButton();

    void	initTextFromInt(gdl::Text &, int, int, int, int);
    void	initTextFromString(gdl::Text &, std::string const &, int, int, int);
    void	initButton(AButton *button, std::string const &text, int x1 , int y1 , int x2, int y2);
    int		centerText(int, std::string const &, int, int);
  };
};

#endif
