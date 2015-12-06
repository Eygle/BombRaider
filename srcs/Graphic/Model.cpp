#include <math.h>
#include <GL/glut.h>
#include "Graphic/Model.hpp"
#include "Database/Database.hpp"

Graphic::Model::Model(Data::e_model model):AObject()
{
  Data	*datas = Data::getInstance();
  Database::Model	infos;
  Database::Database	db;

  db.getModel(infos, datas->modelsName[model]);
  this->_model = gdl::Model::load(infos.path);
  this->_anims.push_back("Idle");
  this->_anims.push_back("Run");
  this->_anims.push_back("Attack");
  this->_anims.push_back("Spell");
  this->_anims.push_back("Death");
  this->_model.cut_animation(this->_model, "Take 001", 0, infos.end_idle, "Idle");
  this->_model.cut_animation(this->_model, "Take 001", infos.end_idle + 1, infos.end_run, "Run");
  this->_model.cut_animation(this->_model, "Take 001", infos.end_run + 1, infos.end_attack, "Attack");
  this->_model.cut_animation(this->_model, "Take 001", infos.end_attack + 1, infos.end_spell, "Spell");
  this->_model.cut_animation(this->_model, "Take 001", infos.end_spell + 1, infos.end_death, "Death");
  this->_model.play("Idle", gdl::Anim::LOOP);
  this->_angle = infos.direction;
}

Graphic::Model::~Model(){}

void	Graphic::Model::unload(){}

void	Graphic::Model::initialize(){}

void	Graphic::Model::update(gdl::GameClock *clock)
{
  this->_model.update(*clock);
}

bool	Graphic::Model::setAnimation(std::string animation)
{
  for (std::vector<std::string>::iterator anim = this->_anims.begin();
       anim != this->_anims.end();
       anim++)
    if (this->_model.animation_hasStarted(*anim))
      {
	if (*anim != "Idle" && *anim != "Run" &&
	    !this->_model.anim_is_ended(*anim))
	  return (false);
	this->_model.stop_animation(*anim);
      }
  if (animation == "Idle" || animation == "Run")
    this->_model.play(animation, gdl::Anim::LOOP);
  else
    this->_model.play(animation);
  return (true);
}

void	Graphic::Model::draw()
{
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(this->_pos.x, this->_pos.y, this->_pos.z);
  glRotatef(this->_rot.x, 1.0, 0.0, 0.0);
  glRotatef(this->_rot.y - this->_angle, 0.0, 1.0, 0.0);
  glRotatef(this->_rot.z, 0.0, 0.0, 1.0);
  this->_model.draw();
  glPopMatrix();
}
