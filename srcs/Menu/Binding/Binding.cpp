#include "Menu/Binding/Binding.hpp"
#include "Menu/SelectPlayerArrayButton.hpp"

namespace Menu
{
  Binding::Binding()
    : imgPos_(0, 0, 0, 0)
  {
    this->camera_.init();
    this->datas_ = Data::getInstance();
    this->keySelected_ = 0;

    this->initMap();

    SelectPlayerArrayButton *back = new SelectPlayerArrayButton(0, true);
    back->setPosition(368, 573, 434, 632);
    this->buttons_.push_back(back);

    this->createImg(Data::BINDINGS_BACK, 332, 207, 1023, 648);

    this->createImg(Data::BINDINGS_KEY_BACK, 402, 295, 580, 314);
    this->createImg(Data::BINDINGS_KEY_BACK, 402, 321, 580, 340);
    this->createImg(Data::BINDINGS_KEY_BACK, 402, 347, 580, 366);
    this->createImg(Data::BINDINGS_KEY_BACK, 402, 373, 580, 392);
    this->createImg(Data::BINDINGS_KEY_BACK, 402, 399, 580, 418);
    this->createImg(Data::BINDINGS_KEY_BACK, 402, 425, 580, 444);
    this->createImg(Data::BINDINGS_KEY_BACK, 402, 451, 580, 470);
    this->createImg(Data::BINDINGS_KEY_BACK, 402, 477, 580, 496);
    this->createImg(Data::BINDINGS_KEY_BACK, 402, 503, 580, 522);

    this->createKeyButton(0, State::MOVE_UP, 617, 295, 796, 314);
    this->createKeyButton(0, State::MOVE_DOWN, 617, 321, 796, 340);
    this->createKeyButton(0, State::TURN_LEFT, 617, 347, 796, 366);
    this->createKeyButton(0, State::TURN_RIGHT, 617, 373, 796, 392);
    this->createKeyButton(0, State::SKILL, 617, 399, 796, 418);
    this->createKeyButton(0, State::SLOT_1, 617, 425, 796, 444);
    this->createKeyButton(0, State::SLOT_2, 617, 451, 796, 470);
    this->createKeyButton(0, State::SLOT_3, 617, 477, 796, 496);
    this->createKeyButton(0, State::CLASSICAL_BOMB, 617, 503, 796, 522);

    this->createKeyButton(1, State::MOVE_UP, 813, 295, 991, 314);
    this->createKeyButton(1, State::MOVE_DOWN, 813, 321, 991, 340);
    this->createKeyButton(1, State::TURN_LEFT, 813, 347, 991, 366);
    this->createKeyButton(1, State::TURN_RIGHT, 813, 373, 991, 392);
    this->createKeyButton(1, State::SKILL, 813, 399, 991, 418);
    this->createKeyButton(1, State::SLOT_1, 813, 425, 991, 444);
    this->createKeyButton(1, State::SLOT_2, 813, 451, 991, 470);
    this->createKeyButton(1, State::SLOT_3, 813, 477, 991, 496);
    this->createKeyButton(1, State::CLASSICAL_BOMB, 813, 503, 991, 522);


    this->createImg(Data::BINDINGS_KEY_BACK, 610, 532, 691, 547);
    this->createImg(Data::BINDINGS_KEY_BACK, 707, 532, 788, 547);
    this->createImg(Data::BINDINGS_KEY_BACK, 804, 532, 885, 547);
    this->createImg(Data::BINDINGS_KEY_BACK, 901, 532, 982, 547);

    this->createImg(Data::BINDINGS_KEY_BACK, 504, 558, 587, 573);
    this->createImg(Data::BINDINGS_KEY_BACK, 504, 585, 587, 600);
    this->createImg(Data::BINDINGS_KEY_BACK, 504, 612, 587, 627);

    this->createCheckButton(0, 1, 643, 558, 658, 573);
    this->createCheckButton(0, 2, 643, 585, 658, 600);
    this->createCheckButton(0, 3, 643, 612, 658, 627);

    this->createCheckButton(1, 1, 738, 558, 753, 573);
    this->createCheckButton(1, 2, 738, 585, 753, 600);
    this->createCheckButton(1, 3, 738, 612, 753, 627);

    this->createCheckButton(2, 1, 837, 558, 852, 573);
    this->createCheckButton(2, 2, 837, 585, 852, 600);
    this->createCheckButton(2, 3, 837, 612, 852, 627);

    this->createCheckButton(3, 1, 932, 558, 947, 573);
    this->createCheckButton(3, 2, 932, 585, 947, 600);
    this->createCheckButton(3, 3, 932, 612, 947, 627);

    std::string	tmp;
    int		size = 12;

    tmp = this->datas_->db.getText(this->datas_->gameSettings.language, "forward");
    this->createTxt(tmp, this->centerText(402, tmp, size, 178), 296, size);
    tmp = this->datas_->db.getText(this->datas_->gameSettings.language, "backward");
    this->createTxt(tmp, this->centerText(402, tmp, size, 178), 322, size);
    tmp = this->datas_->db.getText(this->datas_->gameSettings.language, "left");
    this->createTxt(tmp, this->centerText(402, tmp, size, 178), 348, size);
    tmp = this->datas_->db.getText(this->datas_->gameSettings.language, "right");
    this->createTxt(tmp, this->centerText(402, tmp, size, 178), 374, size);
    tmp = this->datas_->db.getText(this->datas_->gameSettings.language, "skill");
    this->createTxt(tmp, this->centerText(402, tmp, size, 178), 400, size);
    tmp = this->datas_->db.getText(this->datas_->gameSettings.language, "inventory") + " 1";
    this->createTxt(tmp, this->centerText(402, tmp, size, 178), 426, size);
    tmp = this->datas_->db.getText(this->datas_->gameSettings.language, "inventory") + " 2";
    this->createTxt(tmp, this->centerText(402, tmp, size, 178), 452, size);
    tmp = this->datas_->db.getText(this->datas_->gameSettings.language, "inventory") + " 3";
    this->createTxt(tmp, this->centerText(402, tmp, size, 178), 478, size);
    tmp = this->datas_->db.getText(this->datas_->gameSettings.language, "drop_bomb");
    this->createTxt(tmp, this->centerText(402, tmp, size, 178), 504, size);

    tmp = "Key 1";
    this->createTxt(tmp, this->centerText(504, tmp, size, 83), 558, size);
    tmp = "Key 2";
    this->createTxt(tmp, this->centerText(504, tmp, size, 83), 585, size);
    tmp = this->datas_->db.getText(this->datas_->gameSettings.language, "controller");
    this->createTxt(tmp, this->centerText(504, tmp, size, 83), 612, size);

    tmp = this->datas_->db.getText(this->datas_->gameSettings.language, "player") + " 1";
    this->createTxt(tmp, this->centerText(610, tmp, size, 81), 532, size);
    tmp = this->datas_->db.getText(this->datas_->gameSettings.language, "player") + " 2";
    this->createTxt(tmp, this->centerText(707, tmp, size, 81), 532, size);
    tmp = this->datas_->db.getText(this->datas_->gameSettings.language, "player") + " 3";
    this->createTxt(tmp, this->centerText(804, tmp, size, 81), 532, size);
    tmp = this->datas_->db.getText(this->datas_->gameSettings.language, "player") + " 4";
    this->createTxt(tmp, this->centerText(901, tmp, size, 81), 532, size);

    this->focus_ = this->buttons_.begin();
    //    (*this->buttons_.begin())->setFocus(true);
    this->setBackground(Data::BG_MENU);
  }

  Binding::~Binding()
  {
  }

  void	Binding::createImg(Data::e_image id, int x1, int y1, int x2, int y2)
  {
    this->imgPos_.setPos(x1, y1, x2, y2);
    this->bindImgs_.push_back(Graphic::GuiImage(this->imgPos_, &this->datas_->imgs[id]));
  }

  void	Binding::createTxt(std::string &str, int x, int y, int size)
  {
    gdl::Text	tmp;

    tmp.setText(str);
    tmp.setPosition(x, y);
    tmp.setSize(size);
    this->bindTxts_.push_back(tmp);
  }

  void	Binding::createCheckButton(int id, int line, int x1, int y1, int x2, int y2)
  {
    CheckBox	*checkBox = new CheckBox(id, line, x1, y1, x2, y2, this->checkButtons_);

    this->checkButtons_.push_back(checkBox);
    this->buttons_.push_back(checkBox);
  }

  void	Binding::createKeyButton(int player, State::e_ArcadeAction action, int x1, int y1, int x2, int y2)
  {
    KeyButton	*button = new KeyButton(this->keyButtons_, this->events_, this->map_,
		       player, static_cast<int>(action), x1, y1, x2, y2);
    this->keyButtons_.push_back(button);
    this->buttons_.push_back(button);
  }

  void	Binding::initMap()
  {
    this->map_[Input::A] = "A";
    this->map_[Input::B] = "B";
    this->map_[Input::C] = "C";
    this->map_[Input::D] = "D";
    this->map_[Input::E] = "E";
    this->map_[Input::F] = "F";
    this->map_[Input::G] = "G";
    this->map_[Input::H] = "H";
    this->map_[Input::I] = "I";
    this->map_[Input::K] = "J";
    this->map_[Input::K] = "K";
    this->map_[Input::L] = "L";
    this->map_[Input::M] = "M";
    this->map_[Input::N] = "N";
    this->map_[Input::O] = "O";
    this->map_[Input::P] = "P";
    this->map_[Input::Q] = "Q";
    this->map_[Input::R] = "R";
    this->map_[Input::S] = "S";
    this->map_[Input::T] = "T";
    this->map_[Input::U] = "U";
    this->map_[Input::V] = "V";
    this->map_[Input::W] = "W";
    this->map_[Input::X] = "X";
    this->map_[Input::Y] = "Y";
    this->map_[Input::Z] = "Z";
    this->map_[Input::Num0] = "0";
    this->map_[Input::Num1] = "1";
    this->map_[Input::Num2] = "2";
    this->map_[Input::Num3] = "3";
    this->map_[Input::Num4] = "4";
    this->map_[Input::Num5] = "5";
    this->map_[Input::Num6] = "6";
    this->map_[Input::Num7] = "7";
    this->map_[Input::Num8] = "8";
    this->map_[Input::Num9] = "9";
    this->map_[Input::LControl] = "LControl";
    this->map_[Input::LShift] = "LShift";
    this->map_[Input::LAlt] = "LAlt";
    this->map_[Input::LSystem] = "LSystem";
    this->map_[Input::RControl] = "RControl";
    this->map_[Input::RShift] = "RShift";
    this->map_[Input::RAlt] = "RAlt";
    this->map_[Input::RSystem] = "RSystem";
    this->map_[Input::Menu] = "Menu";
    this->map_[Input::LBracket] = "LBracket";
    this->map_[Input::RBracket] = "RBracket";
    this->map_[Input::SemiColon] = "SemiColon";
    this->map_[Input::Comma] = "Comma";
    this->map_[Input::Period] = "Period";
    this->map_[Input::Quote] = "Quote";
    this->map_[Input::Slash] = "Slash";
    this->map_[Input::BackSlash] = "BackSlash";
    this->map_[Input::Tilde] = "Tilde";
    this->map_[Input::Equal] = "Equal";
    this->map_[Input::Dash] = "Dash";
    this->map_[Input::Space] = "Space";
    this->map_[Input::Return] = "Return";
    this->map_[Input::Back] = "Back";
    this->map_[Input::Tab] = "Tab";
    this->map_[Input::PageUp] = "PageUp";
    this->map_[Input::PageDown] = "PageDown";
    this->map_[Input::End] = "End";
    this->map_[Input::Home] = "Home";
    this->map_[Input::Insert] = "Insert";
    this->map_[Input::Delete] = "Delete";
    this->map_[Input::Add] = "Add";
    this->map_[Input::Subtract] = "Subtract";
    this->map_[Input::Multiply] = "Multiply";
    this->map_[Input::Divide] = "Divide";
    this->map_[Input::Left] = "Left";
    this->map_[Input::Right] = "Right";
    this->map_[Input::Up] = "Up";
    this->map_[Input::Down] = "Down";
    this->map_[Input::Numpad0] = "Numpad0";
    this->map_[Input::Numpad1] = "Numpad1";
    this->map_[Input::Numpad2] = "Numpad2";
    this->map_[Input::Numpad3] = "Numpad3";
    this->map_[Input::Numpad4] = "Numpad4";
    this->map_[Input::Numpad5] = "Numpad5";
    this->map_[Input::Numpad6] = "Numpad6";
    this->map_[Input::Numpad7] = "Numpad7";
    this->map_[Input::Numpad8] = "Numpad8";
    this->map_[Input::Numpad9] = "Numpad9";
    this->map_[Input::F1] = "F1";
    this->map_[Input::F2] = "F2";
    this->map_[Input::F3] = "F3";
    this->map_[Input::F4] = "F4";
    this->map_[Input::F5] = "F5";
    this->map_[Input::F6] = "F6";
    this->map_[Input::F7] = "F7";
    this->map_[Input::F8] = "F8";
    this->map_[Input::F9] = "F9";
    this->map_[Input::F10] = "F10";
    this->map_[Input::F11] = "F11";
    this->map_[Input::F12] = "F12";
    this->map_[Input::F13] = "F13";
    this->map_[Input::F14] = "F14";
    this->map_[Input::F15] = "F15";
    this->map_[Input::Pause] = "Pause";
    this->map_[Input::Count] = "Count";
  }

  void	Binding::update()
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
    		  {
		    if (dynamic_cast<KeyButton *>(*it))
		      {
			if (this->keySelected_)
			  this->keySelected_->setSelected(false);
			(*it)->setSelected(true);
			this->keySelected_ = dynamic_cast<KeyButton *>(*it);
		      }
		    else if (dynamic_cast<SelectPlayerArrayButton *>(*it))
		      this->datas_->states->pop();
		    else
		      (*it)->action(0);
		  }
    		else if (mouse.mouseState == Input::PRESSED)
    		  (*it)->activatePress();
    		else
    		  (*it)->activateHover();
    	      }
    	    break;
    	  }
      }

    if (this->keySelected_)
      {
	if (!this->events_->keyEmpty())
	  {
	    Input::Key key = this->events_->popKey().getKeys();
	    if (this->map_.find(key) != this->map_.end())
	      {
		this->keySelected_->action(key);
		this->keySelected_->setSelected(false);
		this->keySelected_ = 0;
	      }
	  }
      }

    this->events_->emptyKey();
    this->events_->emptyMouse();
  }

  void	Binding::draw()
  {
    this->background_.draw();
    for (unsigned int i = 0; i < this->bindImgs_.size(); i++)
      this->bindImgs_[i].draw();
    for (unsigned int i = 0; i < this->bindTxts_.size(); i++)
      this->bindTxts_[i].draw();
    this->drawButton();
  }

  void	Binding::reset()
  {
  }
}
