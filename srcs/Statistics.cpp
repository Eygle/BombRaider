#include "Statistics.hpp"

//
// CTOR / DTOR / ASSIGN
//

Statistics::Statistics(int crit, int def, int hp, int hp_max, int mana,
		       int mana_max, int power, int range, int resi, int speed)
{
  this->_stats = new int[LAST];
  this->_stats[CRITICAL] = crit;
  this->_stats[DEFENSE] = def;
  this->_stats[HP] = hp;
  this->_stats[HP_MAX] = hp_max;
  this->_stats[MANA] = mana;
  this->_stats[MANA_MAX] = mana_max;
  this->_stats[POWER] = power;
  this->_stats[RANGE] = range;
  this->_stats[RESILIENCE] = resi;
  this->_stats[SPEED] = speed;
}

Statistics::Statistics(Statistics const &other)
{
  this->_stats = new int[LAST];
  for (int i = 0, last = static_cast<int>(Statistics::LAST) ; i < last ; ++i)
    {
      Statistics::e_stat tmp = static_cast<Statistics::e_stat>(i);
      this->_stats[i] = other.get(tmp);
    }
}

Statistics::Statistics(int *stats)
{
  this->_stats = new int[LAST];
  for (int i = 0, last = static_cast<int>(Statistics::LAST) ; i < last ; i++)
    this->_stats[i] = stats[i];
}

Statistics::~Statistics()
{
  delete [] this->_stats;
}

Statistics	&Statistics::operator=(Statistics const &other)
{
  if (&other != this)
    {
      for (int i = 0, last = static_cast<int>(Statistics::LAST) ; i < last ; ++i)
	{
	  Statistics::e_stat tmp = static_cast<Statistics::e_stat>(i);
	  this->_stats[i] = other.get(tmp);
	}
    }
  return *this;
}

//
// GETTER
//

int	Statistics::get(e_stat to_get) const
{
  return this->_stats[to_get];
}


//
// PRIVATE FUNCTIONS
//

Statistics::e_gauge_statut	Statistics::checkLimit(e_stat to_change, e_stat max)
{
  if (this->_stats[to_change] > this->_stats[max])
    {
      this->_stats[to_change] = this->_stats[max];
      return Statistics::FULL;
    }
  else if (this->_stats[to_change] < 0)
    {
      this->_stats[to_change] = 0;
      return Statistics::EMPTY;
    }
  return Statistics::GOOD;
}

//
// PUBLIC FUNCTIONS
//

Statistics::e_gauge_statut	Statistics::add(e_stat to_change, int to_add)
{
  if (to_change == SPEED && this->_stats[SPEED] < 0)
    this->_stats[SPEED] *= -1;
  this->_stats[to_change] += to_add;
  if (to_change == HP)
    return (this->checkLimit(to_change, HP_MAX));
  else if (to_change == MANA)
    return (this->checkLimit(to_change, MANA_MAX));
  return Statistics::GOOD;
}

Statistics::e_gauge_statut	Statistics::add(Statistics const &other)
{
  for (int i = 0, last = static_cast<int>(Statistics::LAST) ; i < last ; ++i)
    {
      Statistics::e_stat tmp = static_cast<Statistics::e_stat>(i);
      int value = other.get(tmp);
      if (value != 0)
	this->add(tmp, value);
    }
  return Statistics::GOOD;
}

Statistics::e_gauge_statut	Statistics::sub(e_stat to_change, int to_sub)
{
  this->_stats[to_change] -= to_sub;
  if (to_change == HP)
    return (this->checkLimit(to_change, HP_MAX));
  else if (to_change == MANA)
    return (this->checkLimit(to_change, MANA_MAX));
  return Statistics::GOOD;
}

Statistics::e_gauge_statut	Statistics::sub(Statistics const &other)
{
  for (int i = 0, last = static_cast<int>(Statistics::LAST) ; i < last ; ++i)
    {
      Statistics::e_stat tmp = static_cast<Statistics::e_stat>(i);
      int value = other.get(tmp);
      if (value != 0)
	this->sub(tmp, value);
    }
  return Statistics::GOOD;
}

//
// OPERATOR
//

Statistics &Statistics::operator+=(Statistics const &other)
{
  this->add(other);
  return (*this);
}

Statistics &Statistics::operator-=(Statistics const &other)
{
  this->sub(other);
  return (*this);
}
