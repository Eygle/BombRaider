#ifndef  __SWITCHER__
#define  __SWITCHER__


#include <sstream>
#include "Data.hpp"
#include "AButton.hpp" 

namespace Menu 
{
  class Switcher : public AButton
  {
  protected :
    unsigned int		max_;
    unsigned int		min_;
    unsigned int		value_;
    Graphic::ImagePosition 	cposition_;
    Graphic::ImagePosition 	bposition_;
    Graphic::GuiImage		cursor_;
    Data			*data_;
    std::string			svalue_;
    std::string			pvalue_;
  public :
    Switcher();
    virtual ~Switcher();
    
    virtual void	update() = 0;
    virtual void	action(char c) = 0;
    virtual void	draw();

    bool		isSelected(int x, int y);
    void		modifieValue(int y);
    void		updateFromValue();
  };
};

#endif
