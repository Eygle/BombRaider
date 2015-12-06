#include "Champion/Chogath.hpp"
#include "Champion/ChogathSkill.hpp"
#include "Data.hpp"

Champion::Chogath::Chogath(): Champion()
{
  Data *bobData = Data::getInstance();

  this->_avatarFull = &bobData->imgs[Data::CHOGATH_FULL_AVATAR];
  this->_avatarSmall = &bobData->imgs[Data::CHOGATH_SMALL_AVATAR];
  this->_skillIcon = &bobData->imgs[Data::CHOGATH_SKILL_ICON];
  this->_skillDarkIcon = &bobData->imgs[Data::CHOGATH_SKILL_DARK_ICON];
  this->_model = new Graphic::Model(Data::CHOGATH_MODEL);
  this->_skill = new Skill::ChogathSkill;
  this->_name = "chogath";
  this->_stats = Statistics(5, 15, 100, 100, 10, 10, 10, 1, 5, 5);
  this->_skillTag = "chogath_skill";
}
