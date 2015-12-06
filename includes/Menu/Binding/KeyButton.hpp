#ifndef KEYBUTTON_H_
# define KEYBUTTON_H_

# include "Menu/AButton.hpp"

namespace Menu
{
  class KeyButton : public AButton
  {
  public:
    KeyButton(std::vector<KeyButton *> &, Input::EventManager *, std::map<Input::Key, std::string> &,
	      int, int, int, int, int, int);
    ~KeyButton();

    void	action(char);
    void	update();
    int		getKey() const;
    void	deleteKey();

  private:
    gdl::Text				text_;
    std::map<Input::Key, std::string>	&map_;
    std::vector<KeyButton *>		&other_;
    Input::EventManager			*events_;
    int					player_;
    int					action_;
    int					key_;
    Data				*datas_;

    void	deleteOtherKeys();

    KeyButton();
    KeyButton(KeyButton const &);
    KeyButton &operator=(KeyButton const &);
  };
};

#endif
