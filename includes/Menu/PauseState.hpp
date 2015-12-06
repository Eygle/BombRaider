#ifndef __PAUSESTATE__
#define __PAUSESTATE__

# include "MenuState.hpp"
# include "Menu/SwitchStateButton.hpp"
# include "Menu/SaveButton.hpp"
# include "Data.hpp"

namespace Menu
{
class PauseState : public MenuState
  {
  private:
    Graphic::GuiImage		layout_;
    SaveButton			*saveButton_;

  public :
    PauseState();
    ~PauseState();
    virtual void	draw();
    virtual void	update();
    virtual void	reset();
    void		init();
  };
};
#endif
