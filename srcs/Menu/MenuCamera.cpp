#include <GL/gl.h>
#include <GL/glu.h>

#include "Menu/MenuCamera.hpp"

namespace Menu
{
  MenuCamera::MenuCamera(void)
    : position_(0.0f, 0.0f, 0.0f), rotation_(0.0f, 0.0f, 0.0f)
  {
  }

  MenuCamera::~MenuCamera(void)
  {
  }
  
  void MenuCamera::init(void)
  {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0f, 1366.0f/768.0f, 1.0f, 10000.0f);
    gluLookAt(position_.x, position_.y, position_.z,
	      0.0f, 0.0f, -1.0f,
	      0.0f, 1.0f, 0.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
  }
}
