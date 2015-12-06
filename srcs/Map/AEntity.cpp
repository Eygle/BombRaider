#include <cstdlib>

#include "Map/AEntity.hpp"
#include "Graphic/Graphic.hpp"

//
// CTOR / DTOR / ASSIGN
//

Map::AEntity::AEntity(e_item type, e_category category, bool isBlocking, int x, int y)
  : _type(type), _category(category), _isBlocking(isBlocking),
    _prev(0), _now(new Status())
{
  this->_prev = new Status(*this->_now);
  if (category == Map::BUFF || category == Map::RESSOURCE)
    this->_model = Graphic::Graphic::loadItemModel(type, 0.33);
  else
    this->_model = Graphic::Graphic::loadItemModel(type);
  this->_now->position.x = static_cast<float>(x) + 0.5;
  this->_now->position.y = 0.5;
  this->_now->position.z = static_cast<float>(y) + 0.5;
}

Map::AEntity::~AEntity()
{
  if (this->_prev)
    delete this->_prev;
  if (this->_now)
    delete this->_now;
  if (this->_model)
    delete this->_model;
}

Map::AEntity::AEntity(Map::AEntity const &)
{
}

Map::AEntity& Map::AEntity::operator=(Map::AEntity const &)
{
  return (*this);
}

void	Map::AEntity::update()
{
  if (!this->_prev)
    this->_prev = new Status;
}

//
// GETTER / SETTER
//

Map::e_item	Map::AEntity::getType() const
{
  return (this->_type);
}

Map::e_category Map::AEntity::getCategory() const
{
  return (this->_category);
}

Graphic::AObject	*Map::AEntity::getModel() const
{
  return (this->_model);
}

void Map::AEntity::setModel(Graphic::AObject *model)
{
  this->_model = model;
}

bool Map::AEntity::isBlocking() const
{
  return (this->_isBlocking);
}

Status *Map::AEntity::getPrevStatus() const
{
  return (this->_prev);
}

Status *Map::AEntity::getNowStatus() const
{
  return (this->_now);
}

void	Map::AEntity::save(TiXmlElement *, GameInfo *)
{
}
