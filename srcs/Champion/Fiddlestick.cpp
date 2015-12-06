#include "Champion/Fiddlestick.hpp"
#include "Champion/BuffSkill.hpp"
#include "Statistics.hpp"
#include "Data.hpp"

Champion::Fiddlestick::Fiddlestick(): Champion()
{
  Data *bobData = Data::getInstance();
  Statistics	skillStats(0, 0, 0, 0, 0, 0, 0, 3, 0, 0);
  this->_avatarFull = &bobData->imgs[Data::FIDDLESTICK_FULL_AVATAR];
  this->_avatarSmall = &bobData->imgs[Data::FIDDLESTICK_SMALL_AVATAR];
  this->_skillIcon = &bobData->imgs[Data::FIDDLESTICK_SKILL_ICON];
  this->_skillDarkIcon = &bobData->imgs[Data::FIDDLESTICK_SKILL_DARK_ICON];
  this->_model = new Graphic::Model(Data::FIDDLESTICK_MODEL);
  this->_skill = new Skill::BuffSkill(skillStats, 15, 8.0, 15.0);
  this->_name = "fiddlestick";
  this->_stats = Statistics(5, 5, 80, 80, 15, 15, 25, 2, 3, 8);
  this->_skillTag = "fiddlestick_skill";
}
