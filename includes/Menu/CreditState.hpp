#ifndef CREDITSTATE_H_
# define CREDITSTATE_H_

# include "Menu/MenuState.hpp"
# include "Data.hpp"

namespace Menu
{
  class CreditState : public MenuState
  {
  public:
    CreditState();
    ~CreditState();

    void	draw();
    void	update();

  private:
    CreditState(CreditState const &);
    CreditState &operator=(CreditState const &);
  };
};

#endif
