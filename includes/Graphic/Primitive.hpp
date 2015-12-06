//
// Primitive.hpp for Bomberman in /home/decene_a//Projets/BomberMan/Tests/Objects
// 
// Made by alexandre deceneux
// Login   <decene_a@epitech.net>
// 
// Started on  Mon May  6 17:34:46 2013 alexandre deceneux
// Last update Fri May 31 20:32:14 2013 alexandre deceneux
//

#ifndef	___PRIMITIVE___
#define	___PRIMITIVE___

#include "Graphic/GuiImage.hpp"
#include "Graphic/AObject.hpp"

namespace Graphic
{
  namespace Primitive
  {
    class       Plan : public AObject
    {

    public:

      Plan(float width = 1.0, float height = -1.0, Image *texture = 0);
      ~Plan();

      void      setDim(float width = 1.0, float height = -1.0);
      void      initialize();
      void      update(gdl::GameClock *clock);
      void      draw();
      void      unload();

    private:

      float		_width;
      float		_height;
      Image		*_texture;
    };

    class	Box : public AObject
    {

    public:
      
      Box(float width = 1.0, float height = -1.0, float depth = -1.0, Image *texture = 0);
      ~Box();

      void	setDim(float width = 1.0, float height = -1.0, float depth = -1.0);
      void	initialize();
      void	update(gdl::GameClock *clock);
      void	draw();
      void	unload();

    private:
    
      float		_width;
      float		_height;
      float		_depth;
      Image		*_texture;
    };

    class Sphere : public AObject
    {

    public:

      Sphere(float radius = 0.5, Image *texture = 0);
      ~Sphere();

      void	setRadius(float radius = 0.5);
      void	initialize();
      void	update(gdl::GameClock *clock);
      void	draw();
      void	unload();

    private:

      float	_radius;
      Image		*_texture;
    };
  }
}

#endif
