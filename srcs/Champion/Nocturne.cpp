#include "Champion/Nocturne.hpp"
#include "Champion/BuffSkill.hpp"
#include "Statistics.hpp"
#include "Data.hpp"

Champion::Nocturne::Nocturne() : Champion()
{
  Data *bobData = Data::getInstance();
  Statistics	skillStats(50, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  this->_avatarFull = &bobData->imgs[Data::NOCTURNE_FULL_AVATAR];
  this->_avatarSmall = &bobData->imgs[Data::NOCTURNE_SMALL_AVATAR];
  this->_skillIcon = &bobData->imgs[Data::NOCTURNE_SKILL_ICON];
  this->_skillDarkIcon = &bobData->imgs[Data::NOCTURNE_SKILL_DARK_ICON];
  this->_model = new Graphic::Model(Data::NOCTURNE_MODEL);
  this->_skill = new Skill::BuffSkill(skillStats, 10, 10.0, 30.0);
  this->_name = "nocturne";
  this->_stats = Statistics(20, 10, 100, 100, 10, 10, 15, 1, 5, 8);
  this->_skillTag = "nocturne_skill";
}
