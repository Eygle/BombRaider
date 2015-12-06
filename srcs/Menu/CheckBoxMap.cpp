#include "Menu/CheckBoxMap.hpp"

namespace Menu
{
  CheckBoxMap::CheckBoxMap()
    : checked_(false), data_(Data::getInstance())
  {
    Graphic::ImagePosition	pos(515,445,530,460);
    Graphic::GuiImage		inormal(pos, &(this->data_->imgs[Data::CHECKBOX_UNCHECKED]));
    Graphic::GuiImage		ihover(pos, &(this->data_->imgs[Data::CHECKBOX_CHECKED]));

    this->normal_ = inormal;
    this->hover_ = ihover;
    this->position_  = pos;
    this->checked_ = this->data_->db.getMinimap();
    this->setTextValue(this->data_->db.getText(this->data_->gameSettings.language, "minimap"));
    this->setTextPosition(425, 445);
  }

  CheckBoxMap::~CheckBoxMap()
  {
  }

  void CheckBoxMap::action(char)
  {
    this->checked_ = !this->checked_;
  }

  void CheckBoxMap::update()
  {
    this->data_->gameSettings.minimap = this->checked_;
    this->data_->db.setMinimap(this->checked_);
  }

  void CheckBoxMap::draw()
  {
    if (this->checked_)
      this->hover_.draw();
    else
      this->normal_.draw();
    this->text_.draw();
  }
}
