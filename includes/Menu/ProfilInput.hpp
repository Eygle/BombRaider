#ifndef __PROFILINPUT__
#define __PROFILINPUT__

#include "GameInfo.hpp"
#include "AButton.hpp"

namespace Menu 
{
  class ProfilInput : public AButton
  {
  private :
    std::string			svalue_;
    gdl::Text			tvalue_;
    unsigned int		maxSize_;
    unsigned int		curSize_;
    int				id_;
    GameInfo			*infos_;
  public :
    ProfilInput(int id);
    ~ProfilInput();
    
    virtual void	action(char c);
    virtual void	update();
    virtual void	draw();

    void  init(GameInfo *gameInfos);
    void  initInput(std::string const &text, int y1);
  };
};

#endif
