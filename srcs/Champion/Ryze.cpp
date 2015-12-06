#include "Champion/Ryze.hpp"
#include "Champion/BuffSkill.hpp"
#include "Statistics.hpp"
#include "Data.hpp"

Champion::Ryze::Ryze(): Champion()
{
  Data *bobData = Data::getInstance();
  Statistics	skillStats(0, 0, 0, 0, 0, 0, 20, 0, 0, 0);
  this->_avatarFull = &bobData->imgs[Data::RYZE_FULL_AVATAR];
  this->_avatarSmall = &bobData->imgs[Data::RYZE_SMALL_AVATAR];
  this->_skillIcon = &bobData->imgs[Data::RYZE_SKILL_ICON];
  this->_skillDarkIcon = &bobData->imgs[Data::RYZE_SKILL_DARK_ICON];
  this->_model = new Graphic::Model(Data::RYZE_MODEL);
  this->_skill = new Skill::BuffSkill(skillStats, 15, 10.0, 20.0);
  this->_name = "ryze";
  this->_stats = Statistics(5, 5, 70, 70, 20, 20, 30, 1, 3, 7);
  this->_skillTag = "ryze_skill";
}
