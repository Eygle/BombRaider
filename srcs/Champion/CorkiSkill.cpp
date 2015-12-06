#include "Champion/CorkiSkill.hpp"
#include "Map/MissileBomb.hpp"
#include "Character/Character.hpp"
#include "Data.hpp"

//
// CTOR / DTOR
//

Champion::Skill::CorkiSkill::CorkiSkill()
  : ASkill(15, 0, 15)
{
}

Champion::Skill::CorkiSkill::~CorkiSkill()
{
}

//
// PUBLIC FUNCTIONS
//

bool	Champion::Skill::CorkiSkill::action(Character::Character *corki)
{
  if (this->_isReady && corki->getStat(Statistics::MANA) >= this->_manaConso
      && corki->dropBomb(new Map::MissileBomb(corki, corki->getClock(), 0.0), 0.0, false))
    {
      Data::getInstance()->soundManager->playSound(Sound::CORKI_SKILL_VOICE);
      corki->dropBomb(new Map::MissileBomb(corki, corki->getClock(), 90.0), 0.0, false);
      corki->dropBomb(new Map::MissileBomb(corki, corki->getClock(), 180.0), 0.0, false);
      corki->dropBomb(new Map::MissileBomb(corki, corki->getClock(), -90.0), 0.0, false);
      this->_isUsed = true;
      corki->setStat(Statistics::MANA, -this->_manaConso);
      this->_skillCooldown.play();
      this->_isReady = false;
    }
  return (!this->_isReady);
}

void	Champion::Skill::CorkiSkill::update(Character::Character *)
{
  this->_isUsed = false;
  this->_skillCooldown.update();
  if (this->_skillCooldown.getTotalElapsedTime() > this->_cooldown)
    {
      this->_isReady = true;
      this->_skillCooldown.pause();
      this->_skillCooldown.reset();
    }
}
