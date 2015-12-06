#include "Champion/Minion.hpp"
#include "Champion/CorkiSkill.hpp"
#include "Data.hpp"

Champion::Minion::Minion(): Champion()
{
  Data *bobData = Data::getInstance();

  this->_avatarFull = &bobData->imgs[Data::CORKI_FULL_AVATAR];
  this->_avatarSmall = &bobData->imgs[Data::MINION_SMALL_AVATAR];
  this->_model = new Graphic::Model(Data::MINION_MODEL);
  this->_skill = new Skill::CorkiSkill;
  this->_name = "minion";
  this->_stats = Statistics(20, 5, 120, 120, 15, 15, 20, 1, 10, 10);
  this->_skillTag = "corki_skill";
}
