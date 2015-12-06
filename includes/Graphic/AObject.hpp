//
// AObject.hpp for Bomberman in /home/decene_a//Projets/BomberMan/Tests/Objects
//
// Made by alexandre deceneux
// Login   <decene_a@epitech.net>
//
// Started on  Mon May  6 17:31:12 2013 alexandre deceneux
// Last update Tue Jun  4 19:43:34 2013 Commu
//

#ifndef	___AOBJECT___
#define	___AOBJECT___

#include "GDL/GameClock.hpp"
#include "Graphic/Vector3f.hpp"

namespace Graphic
{
  class	AObject
  {

  public:

  public:

    AObject(void);
    virtual ~AObject();

    virtual void	initialize(void) = 0;
    virtual void	draw(void) = 0;
    virtual void	unload(void) = 0;
    virtual void	update(gdl::GameClock *clock) = 0;

    const Vector3f	&getPos()
    {
      return this->_pos;
    }

    const Vector3f	&getRot()
    {
      return this->_rot;
    }

    void setPos(const Vector3f &position)
    {
      this->_pos = position;
    }
    void setRot(const Vector3f &rotation)
    {
      this->_rot = rotation;
    }

  protected:

    Vector3f _pos;
    Vector3f _rot;
  };
}
#endif
