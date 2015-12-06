#ifndef SELECTPLAYERBUTTON_H_
# define SELECTPLAYERBUTTON_H_

# include "Menu/AButton.hpp"

namespace Menu
{
  class SelectPlayerButton : public AButton
  {
  public:
    SelectPlayerButton(int);
    ~SelectPlayerButton();

    void	update();
    void	action(char);

  private:
    SelectPlayerButton(SelectPlayerButton const &);
    SelectPlayerButton &operator=(SelectPlayerButton const &);
  };
}

#endif
