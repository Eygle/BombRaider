#include "Graphic/GuiImage.hpp"
#include "Menu/MenuState.hpp"

namespace Menu
{
  // CTOR
  MenuState::MenuState() :
    focus_(this->buttons_.begin()), background_(0)
  {
  }

  // DTOR
  MenuState::~MenuState()
  {
  }

  // SETTER
  void	MenuState::setBackground(Data::e_image bg)
  {
    Data *data = Data::getInstance();
    Graphic::ImagePosition pos(0,0,1366,768);
    Graphic::Image *background = &(data->imgs[bg]);
    Graphic::GuiImage ibackground(pos, background);
    this->background_ = ibackground;
  }

  // METHODE
  void	MenuState::draw()
  {
  }

  void	MenuState::update()
  {
  }

  void	MenuState::reset()
  {
  }

  std::list<AButton *>::iterator MenuState::findButtons(int x, int y)
  {
    std::list<AButton *>::iterator it = this->buttons_.begin();
    std::list<AButton *>::iterator end = this->buttons_.end();

    while (it != end)
      {
	if ((*it)->isIn(x, y))
	    return (it);
	++it;
      }
    return (it);
  }

  void	MenuState::nextButton()
  {
    if (this->focus_ == this->buttons_.end())
      this->focus_ = this->buttons_.begin();
    else
      this->focus_++;
  }

  void	MenuState::prevButton()
  {
    if (this->focus_ == this->buttons_.begin())
      this->focus_ =this->buttons_.end();
    else
      this->focus_--;
  }

  void	MenuState::drawButton()
  {
    std::list<AButton *>::iterator it = this->buttons_.begin();
    std::list<AButton *>::iterator end = this->buttons_.end();
    while (it != end)
      {
	(*it)->draw();
	it++;
      }
  }

  void	MenuState::initTextFromString(gdl::Text &text, std::string const &str, int x, int y, int size)
  {
    text.setText(str);
    text.setPosition(x, y);
    text.setSize(size);
  }


  void	MenuState::initTextFromInt(gdl::Text &text, int val, int x, int y, int size)
  {
    std::ostringstream oss;

    oss << val;
    text.setText(oss.str());
    text.setPosition(x, y);
    text.setSize(size);
  }

  void	MenuState::initButton(AButton *button, std::string const &text, int x1, int y1, int x2, int y2)
  {
    button->setTextValue(text);
    button->setTextSize(24);
    button->setPosition(x1, y1, x2, y2);
    button->centerText();
    this->buttons_.push_back(button);
  }

  int	MenuState::centerText(int left, std::string const &text, int size, int totalSize)
  {
    int	x = totalSize / 2;
    int	len = text.length() / 2;

    len *= (size / 2);
    return left + (x - len);
  }
}
