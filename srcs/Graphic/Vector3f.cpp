#include <math.h>
#include "Graphic/Vector3f.hpp"

Graphic::Vector3f::Vector3f(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

Graphic::Vector3f::Vector3f(const Vector3f &copy)
{
  this->x = copy.x;
  this->y = copy.y;
  this->z = copy.z;
}

Graphic::Vector3f	&Graphic::Vector3f::operator=(const Graphic::Vector3f &copy)
{
  this->x = copy.x;
  this->y = copy.y;
  this->z = copy.z;
  return (*this);
}

Graphic::Vector3f	Graphic::Vector3f::operator+(const Graphic::Vector3f &vect)
{
  return (Graphic::Vector3f(this->x + vect.x, this->y + vect.y, this->z + vect.z));
}

Graphic::Vector3f	Graphic::Vector3f::operator-(const Graphic::Vector3f &vect)
{
  return (Graphic::Vector3f(this->x - vect.x, this->y - vect.y, this->z - vect.z));
}

Graphic::Vector3f	Graphic::Vector3f::operator*(const Graphic::Vector3f &vect)
{
  return (Graphic::Vector3f(this->x * vect.x, this->y * vect.y, this->z * vect.z));
}

Graphic::Vector3f	Graphic::Vector3f::operator/(const Graphic::Vector3f &vect)
{
  return (Graphic::Vector3f(this->x / vect.x, this->y / vect.y, this->z / vect.z));
}

Graphic::Vector3f	Graphic::Vector3f::operator+(float value)
{
  return (Graphic::Vector3f(this->x + value, this->y + value, this->z + value));
}

Graphic::Vector3f	Graphic::Vector3f::operator-(float value)
{
  return (Graphic::Vector3f(this->x - value, this->y - value, this->z - value));
}

Graphic::Vector3f	Graphic::Vector3f::operator*(float value)
{
  return (Graphic::Vector3f(this->x * value, this->y * value, this->z * value));
}

Graphic::Vector3f	Graphic::Vector3f::operator/(float value)
{
  return (Graphic::Vector3f(this->x / value, this->y / value, this->z / value));
}

Graphic::Vector3f	&Graphic::Vector3f::operator+=(const Graphic::Vector3f &vect)
{
  *this = (*this) + vect;
  return (*this);
}

Graphic::Vector3f	&Graphic::Vector3f::operator-=(const Graphic::Vector3f &vect)
{
  *this = (*this) - vect;
  return (*this);
}

Graphic::Vector3f	&Graphic::Vector3f::operator*=(const Graphic::Vector3f &vect)
{
  *this = (*this) * vect;
  return (*this);
}

Graphic::Vector3f	&Graphic::Vector3f::operator/=(const Graphic::Vector3f &vect)
{
  *this = (*this) / vect;
  return (*this);
}

Graphic::Vector3f	&Graphic::Vector3f::operator+=(float value)
{
  *this = (*this) + value;
  return (*this);
}


Graphic::Vector3f	&Graphic::Vector3f::operator-=(float value)
{
  *this = (*this) - value;
  return (*this);
}

Graphic::Vector3f	&Graphic::Vector3f::operator*=(float value)
{
  *this = (*this) * value;
  return (*this);
}

Graphic::Vector3f	&Graphic::Vector3f::operator/=(float value)
{
  *this = (*this) / value;
  return (*this);
}

bool		Graphic::Vector3f::operator==(const Graphic::Vector3f &vect)
{
  return (this->x == vect.x && this->y == vect.y && this->z == vect.z);
}

bool		Graphic::Vector3f::operator!=(const Graphic::Vector3f &vect)
{
  return !(*this == vect);
}

Graphic::Vector3f	&Graphic::Vector3f::move_incr(const Graphic::Vector3f &direction, float distance)
{
  float	angle = direction.y * M_PI / 180.0;
  *this += Graphic::Vector3f(- cos(angle) * distance,
			     0,
			     sin(angle) * distance);
  return (*this);
}

Graphic::Vector3f	&Graphic::Vector3f::move_decr(const Graphic::Vector3f &direction, float distance)
{
  float	angle = direction.y * M_PI / 180.0;
  *this -= Graphic::Vector3f(- cos(angle) * distance,
			     0,
			     sin(angle) * distance);
  return (*this);
}
