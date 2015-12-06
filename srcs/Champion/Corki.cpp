#include "Champion/Corki.hpp"
#include "Champion/CorkiSkill.hpp"
#include "Data.hpp"

Champion::Corki::Corki(): Champion()
{
  Data *bobData = Data::getInstance();

  this->_avatarFull = &bobData->imgs[Data::CORKI_FULL_AVATAR];
  this->_avatarSmall = &bobData->imgs[Data::CORKI_SMALL_AVATAR];
  this->_skillIcon = &bobData->imgs[Data::CORKI_SKILL_ICON];
  this->_skillDarkIcon = &bobData->imgs[Data::CORKI_SKILL_DARK_ICON];
  this->_model = new Graphic::Model(Data::CORKI_MODEL);
  this->_skill = new Skill::CorkiSkill;
  this->_name = "corki";
  this->_stats = Statistics(15, 5, 75, 75, 10, 10, 20, 1, 3, 10);
  this->_skillTag = "corki_skill";
}
