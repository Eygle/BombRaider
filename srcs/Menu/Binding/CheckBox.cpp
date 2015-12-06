#include "Menu/Binding/CheckBox.hpp"

namespace Menu
{
  CheckBox::CheckBox(int id, int line, int x1, int y1, int x2, int y2,
		     std::vector<CheckBox *> &list)
    : playerId_(id), line_(line), datas_(Data::getInstance()), list_(list)
  {
    Graphic::ImagePosition	pos(x1, y1, x2, y2);
    Graphic::GuiImage		iNormal(pos, &(this->datas_->imgs[Data::CHECKBOX_UNCHECKED]));
    Graphic::GuiImage		iHover(pos, &(this->datas_->imgs[Data::CHECKBOX_CHECKED]));

    this->checked_ = this->datas_->db.getPlayerController(id) == line - 1;
    this->normal_ = iNormal;
    this->hover_ = iHover;
    this->position_ = pos;
  }

  CheckBox::~CheckBox()
  {
  }

  bool	CheckBox::isChecked() const
  {
    return this->checked_;
  }

  void	CheckBox::setChecked(bool check)
  {
    this->checked_ = check;
    if (check)
      this->datas_->db.setPlayerController(this->playerId_, this->line_ - 1);
  }

  int	CheckBox::getPlayerId() const
  {
    return this->playerId_;
  }

  int	CheckBox::getLine() const
  {
    return this->line_;
  }

  void	CheckBox::changeLinePad()
  {
    std::vector<CheckBox *>::iterator	it;
    int	checked = 0;

    for (it = this->list_.begin(); it != this->list_.end(); ++it)
      if (*it != this && (*it)->getLine() == 2 && (*it)->isChecked())
	checked++;
    if (checked > 1)
      this->changeLine();
  }

  void	CheckBox::changeLine()
  {
    std::vector<CheckBox *>::iterator	it;
    CheckBox				*tmp;
    bool				find = false;

    this->checked_ = false;
    for (int line = 1; line < 3; line++)
      {
	if (line == this->line_)
	  continue;

	bool	checked = false;
	for (it = this->list_.begin(); it != this->list_.end(); ++it)
	  if (*it != this && (*it)->getLine() == line)
	    {
	      if ((*it)->isChecked())
		checked = true;
	      else if ((*it)->getPlayerId() == this->playerId_)
		tmp = *it;
	    }
	if (!checked)
	  {
	    find = true;
	    tmp->setChecked(true);
	    break;
	  }
      }
    if (!find)
      {
	for (it = this->list_.begin(); it != this->list_.end(); ++it)
	  if (*it != this && (*it)->getPlayerId() == this->playerId_ && (*it)->getLine() == 3)
	    {
	      (*it)->setChecked(true);
	      break;
	    }
      }
  }

  void	CheckBox::action(char)
  {
    std::vector<CheckBox *>::iterator	it;
    CheckBox	*tmp = 0;

    if (!this->checked_)
      {
	this->setChecked(true);
	for (it = this->list_.begin(); it != this->list_.end(); ++it)
	  {
	    if (*it != this)
	      {
		if ((*it)->isChecked() && (*it)->getPlayerId() == this->playerId_)
		  (*it)->setChecked(false);
		else if ((*it)->isChecked() && (*it)->getLine() == this->line_)
		  tmp = *it;
	      }
	  }
	if (tmp && this->line_ != -3)
	  tmp->changeLine();
	else if (tmp)
	  tmp->changeLinePad();
      }
  }

  void	CheckBox::update()
  {
  }

  void	CheckBox::draw()
  {
    if (this->checked_)
      this->hover_.draw();
    else
      this->normal_.draw();
  }
}
