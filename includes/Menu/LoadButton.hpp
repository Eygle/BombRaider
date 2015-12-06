#ifndef LOADBUTTON_H_
# define LOADBUTTON_H_

# include "Menu/AButton.hpp"
# include "GameInfo.hpp"

namespace Menu
{
  class LoadButton : public AButton
  {
  public:
    LoadButton();
    ~LoadButton();

    void	update();
    void	action(char);
    void	init(GameInfo *);
  private:
    GameInfo	*gameInfo_;

    LoadButton(LoadButton const &);
    LoadButton &operator=(LoadButton const &);
  };
};

#endif
