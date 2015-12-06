#ifndef CHECKBOX_H_
#define CHECKBOX_H_

#include <vector>

#include "Menu/AButton.hpp"

namespace Menu
{
  class CheckBox : public AButton
  {
  public:
    CheckBox(int, int, int, int, int, int, std::vector<CheckBox *> &);
    ~CheckBox();

    void	action(char);
    void	update();
    void	draw();

    void changeLinePad();
    void changeLine();
    int	 getLine() const;
    int	getPlayerId() const;
    void setChecked(bool);
    bool isChecked() const;

  private:
    int				playerId_;
    int				line_;
    bool			checked_;
    Data			*datas_;

    std::vector<CheckBox *>	&list_;

    CheckBox();
    CheckBox(CheckBox const &);
    CheckBox &operator=(CheckBox const &);
  };
};

#endif
