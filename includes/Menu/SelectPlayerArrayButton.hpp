#ifndef SELECTPLAYERARRAYBUTTON_H_
# define SELECTPLAYERARRAYBUTTON_H_

# include "Menu/AButton.hpp"

namespace Menu
{
  class SelectPlayerArrayButton : public AButton
  {
  public:
    SelectPlayerArrayButton(int, bool);
    ~SelectPlayerArrayButton();

    void	action(char);
    void	update();
  };
};

#endif
