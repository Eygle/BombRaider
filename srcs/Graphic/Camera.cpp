#include <math.h>
#include <GL/glut.h>
#include "Graphic/Camera.hpp"
#include "Data.hpp"

#define ABS(x) (((x) > 0) ? (x) : (-(x)))

Graphic::Camera::Camera()
{
  this->_position = Vector3f(0.0, 0.0, 900.0);
  this->_idealAngle = 0;
  this->_rotation = Vector3f(0.0, 0.0, 0.0);
  this->_to_follow = 0;
  this->_id_cam = 0;
  this->_nb_max_cam = 1;
  this->_range = 0;
}

Graphic::Camera::Camera(int id_cam, int nb_max_cam)
{
  this->_position = Vector3f(0.0, 0.0, 900.0);
  this->_idealAngle = 0;
  this->_rotation = Vector3f(0.0, 0.0, 0.0);
  this->_to_follow = 0;
  this->_id_cam = id_cam;
  this->_nb_max_cam = nb_max_cam;
  this->_range = 0;
}

Graphic::Camera::Camera(const Camera &copy)
{
  this->_position = copy._position;
  this->_idealAngle = copy._idealAngle;
  this->_rotation = copy._rotation;
  this->_to_follow = copy._to_follow;
  this->_id_cam = copy._id_cam;
  this->_nb_max_cam = copy._nb_max_cam;
  this->_range = copy._range;
}

Graphic::Camera	&Graphic::Camera::operator=(const Camera &copy)
{
  this->_position = copy._position;
  this->_idealAngle = copy._idealAngle;
  this->_rotation = copy._rotation;
  this->_to_follow = copy._to_follow;
  this->_id_cam = copy._id_cam;
  this->_nb_max_cam = copy._nb_max_cam;
  this->_range = copy._range;
  return *this;
}

Graphic::Camera::~Camera(){}

void	Graphic::Camera::follow(AObject *to_follow, float range)
{
  this->_to_follow = to_follow;
  this->_range = range + range * (this->_nb_max_cam == 1);
}

void	Graphic::Camera::stopFollowing()
{
  this->_to_follow = 0;
}

void	Graphic::Camera::update()
{
  if (!this->_to_follow)
    return;
  Vector3f	obj_pos = this->_to_follow->getPos();
  this->_idealAngle = (this->_to_follow->getRot().y) * M_PI / 180.0;
  this->_position = obj_pos - Vector3f(- cos(this->_idealAngle) * this->_range,
				       - this->_range * 1.5,
				       sin(this->_idealAngle) * this->_range);
}

void	Graphic::Camera::draw()
{
  Vector3f	obj_pos;
  Data		*datas = Data::getInstance();

  this->update();
  glMatrixMode(GL_PROJECTION);

  if (this->_nb_max_cam == 3)
    glViewport ((datas->gameSettings.screenWidth / 2.0) * (this->_id_cam == 1),
		(datas->gameSettings.screenHeight / 2.0) * (this->_id_cam == 2),
		(datas->gameSettings.screenWidth / 2.0) + (datas->gameSettings.screenWidth / 2.0) * (this->_id_cam == 2),
		(datas->gameSettings.screenHeight / 2.0));
  else if (this->_nb_max_cam == 2)
    glViewport (0,
		(datas->gameSettings.screenHeight / 2.0) * (this->_id_cam == 1),
		datas->gameSettings.screenWidth,
		datas->gameSettings.screenHeight / 2.0);
  else
    glViewport((this->_id_cam % 2) * (datas->gameSettings.screenWidth / 2.0),
	       (this->_id_cam / 2) * (datas->gameSettings.screenHeight / 2.0),
	       (datas->gameSettings.screenWidth / 2.0) + (datas->gameSettings.screenWidth / 2.0) * (this->_nb_max_cam == 1),
	       (datas->gameSettings.screenHeight / 2.0) + (datas->gameSettings.screenHeight / 2.0) * (this->_nb_max_cam == 1)
	       );
  glLoadIdentity();
  if (this->_nb_max_cam == 1 || this->_nb_max_cam == 4)
    gluPerspective(70.0, datas->gameSettings.screenWidth / datas->gameSettings.screenHeight, 1.0, 900000.0);
  else if (this->_nb_max_cam == 2)
    gluPerspective(70.0, datas->gameSettings.screenWidth / (datas->gameSettings.screenHeight / 2.0), 1.0, 900000.0);
  else
    gluPerspective(70.0,
		   ((datas->gameSettings.screenWidth / 2.0) + (datas->gameSettings.screenWidth / 2.0) * (this->_id_cam == 2)) /
		   (datas->gameSettings.screenHeight / 2.0),
		   1.0, 900000.0);
  if (this->_to_follow)
    obj_pos = this->_to_follow->getPos();
  gluLookAt(this->_position.x, this->_position.y, this->_position.z,
	    obj_pos.x, obj_pos.y, obj_pos.z,
            0.0, 1.0, 0.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}
