#include <list>
#include "Data.hpp"
#include "Champion/ChogathSkill.hpp"
#include "Map/AEntity.hpp"
#include "Map/MapCase.hpp"
#include "Statistics.hpp"

//
// CTOR / DTOR
//

Champion::Skill::ChogathSkill::ChogathSkill()
  : ASkill(15, 0, 30)
{
}

Champion::Skill::ChogathSkill::~ChogathSkill()
{
}

//
// PRIVATE FUNCTIONS
//

void	Champion::Skill::ChogathSkill::inflictDmg(int x, int z, Character::Character const *chogath)
{
  Statistics	dmg(0, 0, 0, 0, 0, 0, 50 + chogath->getStat(Statistics::POWER), 0, 0, 0);
  std::list<Map::AEntity *>		&items = chogath->getGameInfo().map->at(x, z).getItems();
  std::list<Character::Character *>	&characters = chogath->getGameInfo().map->at(x, z).getCharacters();

  for (std::list<Map::AEntity *>::iterator it = items.begin(); it != items.end(); ++it)
    {
      if ((*it)->getCategory() == Map::BOMB)
	{
	  (*it)->takeDmg(dmg);
	  it = items.begin();
	}
      if ((*it)->takeDmg(dmg))
	{
	  chogath->getGameInfo().map->at(x, z).removeItem(*it);
	  it = items.begin();
	}
    }
  for (std::list<Character::Character *>::iterator it = characters.begin(); it != characters.end(); ++it)
    {
      if ((*it) != chogath)
	(*it)->takeDmg(dmg);
    }
}

//
// PUBLIC FUNCTIONS
//

bool	Champion::Skill::ChogathSkill::action(Character::Character *chogath)
{
  if (this->_isReady && chogath->getStat(Statistics::MANA) >= this->_manaConso)
    {
      Data::getInstance()->soundManager->playSound(Sound::CHOGATH_SKILL_VOICE);
      Graphic::Vector3f	tmp = chogath->getNowState()->position;
      this->inflictDmg(tmp.x, tmp.z, chogath);
      tmp.move_incr(chogath->getNowState()->direction, 1);
      this->inflictDmg(tmp.x, tmp.z, chogath);
      this->_isUsed = true;
      chogath->setStat(Statistics::MANA, -this->_manaConso);
      this->_skillCooldown.play();
      this->_isReady = false;
    }
  return (!this->_isReady);
}

void	Champion::Skill::ChogathSkill::update(Character::Character *)
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
