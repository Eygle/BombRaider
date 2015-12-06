#include <list>
#include "Menu/CheckBoxLanguage.hpp"

namespace Menu
{
  CheckBoxLanguage::CheckBoxLanguage(Database::e_lang language)
    : checked_(false), associate_(0), language_(language), data_(Data::getInstance())
  {
    Graphic::ImagePosition pos(0,0,0,0);
    Graphic::GuiImage		inormal(pos, &(this->data_->imgs[Data::CHECKBOX_UNCHECKED]));
    Graphic::GuiImage		ihover(pos, &(this->data_->imgs[Data::CHECKBOX_CHECKED]));


    this->normal_ = inormal;
    this->hover_ = ihover;
  }

  CheckBoxLanguage::~CheckBoxLanguage()
  {
  }

  void	CheckBoxLanguage::setAssociate(CheckBoxLanguage *associate)
  {
    this->associate_ = associate;
  }

  void	CheckBoxLanguage::action(char)
  {
    this->checked_ = !this->checked_;
    if (this->associate_->checked_ && this->checked_)
      {
	this->associate_->checked_ = false;
	this->data_->db.setLanguage(static_cast<int>(this->language_ == Database::FRENCH ? Database::FRENCH : Database::ENGLISH));
      }
  }

  void	CheckBoxLanguage::update()
  {
    if (this->checked_)
      {
	this->data_->gameSettings.language = this->language_;
	this->data_->db.setLanguage(this->language_);
      }
  }

  void	CheckBoxLanguage::draw()
  {
    if (!this->checked_)
      this->normal_.draw();
    else
      this->hover_.draw();
    this->text_.draw();
  }

  void getLanguageBox(std::list<AButton *> &result)
  {
    CheckBoxLanguage	*fr = new CheckBoxLanguage(Database::FRENCH);
    CheckBoxLanguage	*en = new CheckBoxLanguage(Database::ENGLISH);
    Data *data = Data::getInstance();

    en->setPosition(910, 445, 925, 460);
    en->setAssociate(fr);
    en->setTextValue(data->db.getText(data->gameSettings.language, "lang_en"));
    en->setTextPosition(940, 445);

    fr->setPosition(760, 445, 775, 460);
    fr->setAssociate(en);
    fr->setTextValue(data->db.getText(data->gameSettings.language, "lang_fr"));
    fr->setTextPosition(790, 445);
    result.push_back(fr);
    result.push_back(en);

    if (data->db.getLanguage() == Database::FRENCH)
      fr->action(0);
    else
      en->action(0);
  }
}
