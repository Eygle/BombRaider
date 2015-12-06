#include "Champion/BuffSkill.hpp"
#include "Character/Character.hpp"

//
// CTOR / DTOR
//

Champion::Skill::BuffSkill::BuffSkill(Statistics const &stats, int mana, float duration, float cooldown)
  : ASkill(mana, duration, cooldown), _skillStats(stats)
{
}

Champion::Skill::BuffSkill::~BuffSkill()
{
}

//
// PUBLIC FUNCTIONS
//

bool	Champion::Skill::BuffSkill::action(Character::Character *character)
{
  if (this->_isReady && character->getStat(Statistics::MANA) >= this->_manaConso)
    {
      if (character->getChampion()->getName() == "fiddlestick")
	Data::getInstance()->soundManager->playSound(Sound::FIDDLE_SKILL_VOICE);
      else if (character->getChampion()->getName() == "ryze")
	Data::getInstance()->soundManager->playSound(Sound::RYZE_SKILL_VOICE);
      else
	Data::getInstance()->soundManager->playSound(Sound::NOCTURNE_SKILL_VOICE);
      character->addStats(this->_skillStats);
      this->_isUsed = true;
      this->_isReady = false;
      this->_skillDuration.reset();
      this->_skillDuration.play();
      this->_skillCooldown.reset();
      this->_skillCooldown.play();
      character->setStat(Statistics::MANA, -this->_manaConso);
    }
  return (!this->_isReady);
}

void	Champion::Skill::BuffSkill::update(Character::Character *character)
{
  this->_skillDuration.update();
  this->_skillCooldown.update();
  if (this->_isUsed && this->_skillDuration.getTotalElapsedTime() >= this->_duration)
    {
      this->_isUsed = false;
      character->subStats(this->_skillStats);
    }
  if (!this->_isUsed && this->_skillCooldown.getTotalElapsedTime() > this->_cooldown)
    this->_isReady = true;
}
