//
// Camera.hpp for Bomberman in /home/decene_a//Projets/BomberMan/Tests
//
// Made by alexandre deceneux
// Login   <decene_a@epitech.net>
//
// Started on  Mon May  6 16:42:35 2013 alexandre deceneux
// Last update Thu Jun  6 13:16:01 2013 alexandre deceneux
//

#ifndef	___CAMERA___
#define	___CAMERA___

#include "Graphic/Vector3f.hpp"
#include "Graphic/AObject.hpp"

namespace Graphic
{

  class	Camera
  {

  public:

    Camera();
    Camera(const Camera &);
    Camera(int id_cam, int nb_max_cam);
    Camera	&operator=(const Camera &);
    ~Camera();

    void	follow(AObject *to_follow, float range = 10.0);
    void	stopFollowing();
    void	update();
    void	draw();

  private:

    AObject	*_to_follow;
    float	_range;
    Vector3f	_position;
    float	_idealAngle;
    Vector3f	_rotation;
    int		_id_cam;
    int		_nb_max_cam;
  };

}

#endif
