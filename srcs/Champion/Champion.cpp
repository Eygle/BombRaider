#include "Champion/Champion.hpp"

//
// CTOR / DTOR
//

Champion::Champion::Champion()
{
  this->_selected = false;
}

//
// GETTER
//

Champion::Champion::~Champion()
{
}

Graphic::Image	*Champion::Champion::getAvatarFull() const
{
  return this->_avatarFull;
}

Graphic::Image	*Champion::Champion::getAvatarSmall() const
{
  return this->_avatarSmall;
}

Graphic::Model		*Champion::Champion::getModel() const
{
  return this->_model;
}

Statistics const	&Champion::Champion::getStats() const
{
  return this->_stats;
}

std::string const	&Champion::Champion::getName() const
{
  return this->_name;
}

bool	Champion::Champion::isSelected() const
{
  return (this->_selected);
}

bool	Champion::Champion::isSkillReady() const
{
  return this->_skill->isReady();
}

bool	Champion::Champion::isSkillActive() const
{
  return this->_skill->isActive();
}

std::string const &Champion::Champion::getSkillTag() const
{
  return this->_skillTag;
}

Graphic::Image	*Champion::Champion::getSkillIcon() const
{
  return this->_skillIcon;
}

Graphic::Image	*Champion::Champion::getSkillDarkIcon() const
{
  return this->_skillDarkIcon;
}

int		Champion::Champion::getSkillTimePercent() const
{
  return (this->_skill->getTimePercent());
}

float		Champion::Champion::getSkillTimeRemain() const
{
  return (this->_skill->getTimeRemain());
}

//
// SETTER
//

void	Champion::Champion::setSelected(bool sel)
{
  this->_selected = sel;
}

//
// PUBLIC FUNCTIONS
//

bool	Champion::Champion::actionSkill(Character::Character *character)
{
  return (this->_skill->action(character));
}

void	Champion::Champion::updateSkill(Character::Character *character)
{
  this->_skill->update(character);
}

void	Champion::Champion::reset()
{
  this->_model->setAnimation("Idle");
  this->_skill->reset();
}
