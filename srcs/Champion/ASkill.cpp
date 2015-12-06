#include "Champion/ASkill.hpp"

//
// CTOR / DTOR
//

Champion::Skill::ASkill::ASkill(int mana, float duration, float cooldown)
  : _duration(duration), _cooldown(cooldown), _manaConso(mana),
    _isUsed(false), _isReady(true)
{
}

Champion::Skill::ASkill::~ASkill()
{
}

//
// GETTER
//

bool	Champion::Skill::ASkill::isActive() const
{
  return this->_isUsed;
}

bool	Champion::Skill::ASkill::isReady() const
{
  return this->_isReady;
}

float	Champion::Skill::ASkill::getTimeRemain() const
{
  float	time = this->_skillCooldown.getTotalElapsedTime();
  return (time > 0 ? this->_cooldown - time : 0);
}

int	Champion::Skill::ASkill::getTimePercent() const
{
  float	time = this->_skillCooldown.getTotalElapsedTime();
  return (time > 0 ? (100 - ((time * 100) / this->_cooldown)) : 0);
}

void	Champion::Skill::ASkill::reset()
{
  this->_isReady = true;
  this->_isUsed = false;
  this->_skillCooldown.reset();
  this->_skillCooldown.pause();
  this->_skillDuration.reset();
  this->_skillCooldown.pause();
}
