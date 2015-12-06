#include "Map/ARessource.hpp"
#include "Character/Character.hpp"

//
// CTOR / DTOR / ASSIGN
//

Map::ARessource::ARessource(Map::e_item type, int x, int y)
  : AEntity(type, Map::RESSOURCE, false, x, y),
    _quantity(2), _icon(0), _isAscending(true)
{
}

Map::ARessource::~ARessource(){}

//
// GETTER
//

Graphic::Image *Map::ARessource::getIcon() const
{
  return (this->_icon);
}

int Map::ARessource::getQuantity() const
{
  return (this->_quantity);
}

void	Map::ARessource::update()
{
  if (this->_isAscending == true)
    {
      this->_now->position.y += 0.01;
      if (this->_now->position.y >= 0.8)
	this->_isAscending = false;
    }
  else
    {
      this->_now->position.y -= 0.01;
      if (this->_now->position.y <= 0.5)
	this->_isAscending = true;
    }
}

//
// PUBLIC FUNCTIONS
//

bool	Map::ARessource::action(Character::Character *charac)
{
  return (charac->takeItem(this));
}

bool	Map::ARessource::takeDmg(Statistics const &)
{
  return (true);
}

void	Map::ARessource::add(int toAdd)
{
  this->_quantity += toAdd;
}
