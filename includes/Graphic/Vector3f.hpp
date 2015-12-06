//
// Vector3f.hpp for Bomberman in /home/decene_a//Projets/BomberMan/Tests/Utils
// 
// Made by alexandre deceneux
// Login   <decene_a@epitech.net>
// 
// Started on  Mon May  6 16:12:19 2013 alexandre deceneux
// Last update Fri May 31 13:59:13 2013 alexandre deceneux
//

#ifndef	___VECTOR3DF___
#define	___VECTOR3DF___

namespace Graphic
{

  struct	Vector3f
  {
    float	x;
    float	y;
    float	z;

    Vector3f(float x = 0.0, float y = 0.0, float z = 0.0);
    Vector3f(const Vector3f& copy);
    Vector3f	&operator=(const Vector3f &copy);
  
    Vector3f	operator+(const Vector3f &vect);
    Vector3f	operator-(const Vector3f &vect);
    Vector3f	operator*(const Vector3f &vect);
    Vector3f	operator/(const Vector3f &vect);

    Vector3f	operator+(float value);
    Vector3f	operator-(float value);
    Vector3f	operator*(float value);
    Vector3f	operator/(float value);

    Vector3f	&operator+=(const Vector3f &vect);
    Vector3f	&operator-=(const Vector3f &vect);
    Vector3f	&operator*=(const Vector3f &vect);
    Vector3f	&operator/=(const Vector3f &vect);

    Vector3f	&operator+=(float value);
    Vector3f	&operator-=(float value);
    Vector3f	&operator*=(float value);
    Vector3f	&operator/=(float value);

    bool	operator==(const Vector3f &vect);
    bool        operator!=(const Vector3f &vect);

    Vector3f	&move_incr(const Vector3f &direction, float distance);
    Vector3f	&move_decr(const Vector3f &direction, float distance);

  };

}

#endif
