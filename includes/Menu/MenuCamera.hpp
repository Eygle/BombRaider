#ifndef __MENUCAMERA__
#define __MENUCAMERA__

#include "../Graphic/Vector3f.hpp"

namespace Menu
{
  class MenuCamera 
  {
  private :
    Graphic::Vector3f position_;
    Graphic::Vector3f rotation_;
  public :
    MenuCamera();
    ~MenuCamera();
    
    void	init();
  };
};
#endif 
