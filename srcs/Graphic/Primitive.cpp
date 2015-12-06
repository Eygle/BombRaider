#include <GL/glut.h>
#include "Graphic/Primitive.hpp"

Graphic::Primitive::Plan::Plan(float width, float height, Image *texture):AObject()
{
  if (width < 0)
    width = 1.0;
  if (height < 0)
    height = width;
  this->_width = width;
  this->_height = height;
  this->_texture = texture;
}

Graphic::Primitive::Plan::~Plan(){}

void	Graphic::Primitive::Plan::unload(){}

void	Graphic::Primitive::Plan::setDim(float width, float height)
{
  if (width < 0)
    width = 1.0;
  if (height < 0)
    height = width;
  this->_width = width;
  this->_height = height;
}

void	Graphic::Primitive::Plan::initialize(){}

void	Graphic::Primitive::Plan::update(gdl::GameClock *)
{
}

void	Graphic::Primitive::Plan::draw()
{
  if (this->_texture)
    this->_texture->bind();
  glBegin(GL_QUADS);

  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(this->_pos.x, this->_pos.y, this->_pos.z);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(this->_pos.x + this->_width, this->_pos.y, this->_pos.z);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(this->_pos.x + this->_width, this->_pos.y, this->_pos.z + this->_height);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(this->_pos.x, this->_pos.y, this->_pos.z + this->_height);

  glEnd();
}


Graphic::Primitive::Box::Box(float width, float height, float depth, Image *texture):AObject()
{
  if (width < 0)
    width = 1.0;
  if (height < 0)
    height = width;
  if (depth < 0)
    depth = width;
  this->_width = width;
  this->_height = height;
  this->_depth = depth;
  this->_texture = texture;
}

Graphic::Primitive::Box::~Box(){}

void	Graphic::Primitive::Box::unload(){}

void	Graphic::Primitive::Box::setDim(float width, float height, float depth)
{
  if (width < 0)
    width = 1.0;
  if (height < 0)
    height = width;
  if (depth < 0)
    depth = width;
  this->_width = width;
  this->_height = height;
  this->_depth = depth;
}

void	Graphic::Primitive::Box::initialize(){}

void	Graphic::Primitive::Box::update(gdl::GameClock *)
{
}

void	Graphic::Primitive::Box::draw()
{
  if (this->_texture)
    this->_texture->bind();

  glPushMatrix();
  glLoadIdentity();
  glTranslatef(this->_pos.x, this->_pos.y, this->_pos.z);
  glRotatef(this->_rot.y, 0.0, 1.0, 0.0);
  glRotatef(this->_rot.x, 1.0, 0.0, 0.0);
  glRotatef(this->_rot.z, 0.0, 0.0, 1.0);

  glBegin(GL_QUADS);

  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(- this->_width / 2.0, + this->_height / 2.0, - this->_depth / 2.0);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(+ this->_width / 2.0, + this->_height / 2.0, - this->_depth / 2.0);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(+ this->_width / 2.0, - this->_height / 2.0, - this->_depth / 2.0);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(- this->_width / 2.0, - this->_height / 2.0, - this->_depth / 2.0);

  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(+ this->_width / 2.0, + this->_height / 2.0, - this->_depth / 2.0);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(+ this->_width / 2.0, + this->_height / 2.0, + this->_depth / 2.0);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(+ this->_width / 2.0, - this->_height / 2.0, + this->_depth / 2.0);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(+ this->_width / 2.0, - this->_height / 2.0, - this->_depth / 2.0);

  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(- this->_width / 2.0, + this->_height / 2.0, + this->_depth / 2.0);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(- this->_width / 2.0, - this->_height / 2.0, + this->_depth / 2.0);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(+ this->_width / 2.0, - this->_height / 2.0, + this->_depth / 2.0);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(+ this->_width / 2.0, + this->_height / 2.0, + this->_depth / 2.0);

  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(- this->_width / 2.0, + this->_height / 2.0, + this->_depth / 2.0);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(- this->_width / 2.0, - this->_height / 2.0, + this->_depth / 2.0);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(- this->_width / 2.0, - this->_height / 2.0, - this->_depth / 2.0);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(- this->_width / 2.0, + this->_height / 2.0, - this->_depth / 2.0);

  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(- this->_width / 2.0, + this->_height / 2.0, - this->_depth / 2.0);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(- this->_width / 2.0, + this->_height / 2.0, + this->_depth / 2.0);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(+ this->_width / 2.0, + this->_height / 2.0, + this->_depth / 2.0);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(+ this->_width / 2.0, + this->_height / 2.0, - this->_depth / 2.0);

  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(- this->_width / 2.0, - this->_height / 2.0, + this->_depth / 2.0);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(+ this->_width / 2.0, - this->_height / 2.0, + this->_depth / 2.0);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(+ this->_width / 2.0, - this->_height / 2.0, - this->_depth / 2.0);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(- this->_width / 2.0, - this->_height / 2.0, - this->_depth / 2.0);

  glEnd();

  glPopMatrix();
}


Graphic::Primitive::Sphere::Sphere(float radius, Image *texture):AObject()
{
  this->_radius = (radius > 0) ? radius : 0.5;
  this->_texture = texture;
}

Graphic::Primitive::Sphere::~Sphere(){}

void	Graphic::Primitive::Sphere::unload(){}

void	Graphic::Primitive::Sphere::setRadius(float radius)
{
  this->_radius = (radius > 0) ? radius : 0.5;
}

void	Graphic::Primitive::Sphere::initialize(){}

void	Graphic::Primitive::Sphere::update(gdl::GameClock *){}

void	Graphic::Primitive::Sphere::draw()
{
  if (this->_texture)
    this->_texture->bind();
  glTexCoord2f(1.0f, 1.0f);
  glTranslatef(this->_pos.x, this->_pos.y - 1000, this->_pos.z);
  glRotatef(180.0, 0, 0, 1);

  GLUquadric* params = gluNewQuadric();
  gluQuadricDrawStyle(params,GLU_FILL);
  gluQuadricTexture(params,GL_TRUE);

  glEnable(GL_DEPTH_TEST);
  glEnable( GL_TEXTURE_2D );
  glDepthFunc(GL_LEQUAL);
  glDepthMask(GL_TRUE);
  glCullFace(GL_BACK);
  glClearDepth(1.f);
  glFrontFace(GL_CCW);
  glDisable(GL_CULL_FACE);

  gluSphere(params, this->_radius / 2.0, 600000.0, 600000.0);
  gluDeleteQuadric(params);
  glRotatef(-180.0, 0, 0, 1);
  glTranslatef(-this->_pos.x, -this->_pos.y + 1000, -this->_pos.z);
}
