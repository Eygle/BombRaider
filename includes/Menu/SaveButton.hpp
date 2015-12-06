#ifndef SAVEBUTTON_H_
# define SAVEBUTTON_H_

# include "Menu/AButton.hpp"
# include "GameInfo.hpp"

namespace Menu
{
  class SaveButton : public AButton
  {
  public:
    SaveButton();
    ~SaveButton();

    void	update();
    void	action(char);
    void	init(GameInfo *);
  private:
    GameInfo	*gameInfo_;

    SaveButton(SaveButton const &);
    SaveButton &operator=(SaveButton const &);
  };
};

#endif
