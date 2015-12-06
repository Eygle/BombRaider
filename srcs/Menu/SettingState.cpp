#include "Menu/SettingState.hpp"
#include "Menu/SettingBackButton.hpp"
#include "Menu/SwitchStateButton.hpp"

namespace Menu
{
  SettingState::SettingState()
    : switcherFocus_(0), layout_(0)
  {
    Data *data = Data::getInstance();
    Graphic::ImagePosition	layoutp(332,207,1023,648);
    this->soundSwitcher_ = initSoundSwitcher();

    Graphic::GuiImage		layout(layoutp, &(data->imgs[Data::LAYOUT_OPTION]));
    this->layout_ = layout;
    getLanguageBox(this->buttons_);
    CheckBoxMap *checki = new CheckBoxMap;

    SettingBackButton *back = new SettingBackButton(this);
    SwitchStateButton *binding = new SwitchStateButton(data->states, false, State::BINDING);
    this->initButton(binding, data->db.getText(data->gameSettings.language, "binding"), 570, 515, 770, 570);
    this->buttons_.push_back(checki);
    this->buttons_.push_back(back);
    this->setBackground(Data::BG_MENU);
  }

  SettingState::~SettingState()
  {
  }

  void	SettingState::draw()
  {
    this->background_.draw();
    this->layout_.draw();
    std::list<SoundSwitcher *>::iterator it = this->soundSwitcher_.begin();
    std::list<SoundSwitcher *>::iterator end = this->soundSwitcher_.end();
    while (it != end)
      {
	(*it)->draw();
	++it;
      }
    this->drawButton();
  }

  void	SettingState::update()
  {
    while (!(this->events_->mouseEmpty()))
      {
	std::list<AButton *>::iterator it;
	Input::s_mouseEvent mouse = this->events_->popMouse();
	if ((it = this->findButtons(mouse.pos.first,mouse.pos.second)) != this->buttons_.end())
	  {
	    if (mouse.clic == gdl::Mouse::Left)
	      {
		if (mouse.mouseState == Input::RELEASE)
		  (*it)->action(0);
		else if (mouse.mouseState == Input::PRESSED)
		  (*it)->activatePress();
		else
		  (*it)->activateHover();
	      }
	    break;
	  }
	else if (mouse.clic == gdl::Mouse::Left && mouse.mouseState == Input::PRESSED)
	    {
	      if (this->switcherFocus_)
		this->switcherFocus_->setValue(mouse.pos.first);
	      else if ((this->switcherFocus_ = this->findSwitcher(mouse.pos.first, mouse.pos.second)))
		this->switcherFocus_->setValue(mouse.pos.first);
	    }
	else if (mouse.clic == gdl::Mouse::Left && mouse.mouseState == Input::RELEASE)
	  this->switcherFocus_ = 0;
      }
    this->events_->emptyKey();
    this->events_->emptyMouse();
  }

  SoundSwitcher *SettingState::findSwitcher(int x, int y)
  {
    std::list<SoundSwitcher *>::iterator it = this->soundSwitcher_.begin();
    std::list<SoundSwitcher *>::iterator end = this->soundSwitcher_.end();
    while (it != end)
      {
	if ((*it)->isSelected(x,y))
	  return (*it);
	++it;
      }
    return (0);
  }

  void	SettingState::reset()
  {
  }

  void	SettingState::save()
  {
    {
      std::list<SoundSwitcher *>::iterator it = this->soundSwitcher_.begin();
      std::list<SoundSwitcher *>::iterator end = this->soundSwitcher_.end();
      while (it != end)
	{
	  (*it)->update();
	  ++it;
	}
    }
    std::list<AButton *>::iterator it = this->buttons_.begin();
    std::list<AButton *>::iterator end = this->buttons_.end();
    while (it != end)
      {
	(*it)->update();
	++it;
      }
  }
}
