#ifndef BINDING_H_
# define BINDING_H_

# include <vector>

# include <GDL/Text.hpp>
# include <GDL/Image.hpp>

# include "Menu/MenuState.hpp"
# include "Menu/Binding/KeyButton.hpp"
# include "Menu/Binding/CheckBox.hpp"
# include "State/StateActions.hpp"
# include "Data.hpp"

namespace Menu
{
  class Binding : public MenuState
  {
  public:
    Binding();
    ~Binding();

    void	update();
    void	draw();
    void	reset();

  private:
    Graphic::ImagePosition	imgPos_;
    Graphic::GuiImage		*bindBackground_;

    Data	*datas_;

    std::vector<Graphic::GuiImage>	bindImgs_;
    std::vector<gdl::Text>		bindTxts_;
    std::vector<KeyButton *>		keyButtons_;
    std::vector<CheckBox *>		checkButtons_;

    std::map<Input::Key, std::string>	map_;

    KeyButton				*keySelected_;

    void	createImg(Data::e_image, int, int, int, int);
    void	createTxt(std::string &, int, int, int);
    void	createKeyButton(int, State::e_ArcadeAction, int, int, int, int);
    void	createCheckButton(int, int, int, int, int, int);
    void	initMap();

    Binding(Binding const &);
    Binding &operator=(Binding const &);
  };
};

#endif
