#ifndef INTROSTATE_H_
# define INTROSTATE_H_

# include "Menu/MenuState.hpp"
# include "Data.hpp"

namespace Menu
{
  class IntroState : public MenuState
  {
  public:
    IntroState();
    ~IntroState();

    void	draw();
    void	update();

  private:
    int			pageNbr_;
    Data::e_image	page_[3];

    IntroState(IntroState const &);
    IntroState &operator=(IntroState const &);
  };
};

#endif
