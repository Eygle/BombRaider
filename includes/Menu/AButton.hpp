
#ifndef __ABUTTON__
#define __ABUTTON__

// STD
#include <string>

// GDL
#include "GDL/Text.hpp"
#include "GDL/Image.hpp"

// BOMBERMAN
#include "../Graphic/GuiImage.hpp"
#include "IButton.hpp"
#include "../Data.hpp"

namespace Menu
{
  class AButton : public IButton
  {
  protected :
    bool			isPressed_;
    bool			isHover_;
    bool			focus_;
    bool			isSelectedDurable_;
    std::string			value_;
    gdl::Text			text_;
    Graphic::ImagePosition	position_;
    Graphic::GuiImage		normal_;
    Graphic::GuiImage		hover_;
    Graphic::GuiImage		pressed_;
    unsigned int		textSize_;
    int				id_;

  public:
    AButton(int id = 0);
    virtual ~AButton();

    // GETTER
    const Graphic::ImagePosition	&getPosition() const;
    bool				getPressed() const;
    // SETTER

    // Text
    void		setTextValue(const std::string &text);
    void		setTextPosition(int x, int y);
    bool		setTextFont(std::string const & fontPath);
    void		setTextColor(gdl::Color const & color);
    void		setTextSize(unsigned int size);
    // Image
    void		setNormal(Graphic::GuiImage &hover);
    void		setHover(Graphic::GuiImage &normal);
    void		setFocus(bool);
    void		setSelected(bool);

    // Position
    void		setPosition(Graphic::ImagePosition const &pos);
    void		setPosition(int x1, int y1, int x2, int y2);

    // GETTER
    const std::string	&getText();
    int			getId() const;

    // METHODE
    virtual void action(char c) = 0;
    virtual void update() = 0;
    virtual void draw();

    // MEMBER FUNCTION
    bool	isIn(float x, float y) const;
    void	centerText();
    void	initAffichage(Data::e_image normal, Data::e_image hover,
				       Data::e_image pressed, Graphic::ImagePosition const &pos);
    void	activateHover();
    void	activatePress();
    void	desactivatePress();
  };
};
#endif
