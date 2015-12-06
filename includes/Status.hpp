#ifndef __STATUS_HPP__
# define __STATUS_HPP__

#include "Graphic/Vector3f.hpp"

struct Status
{
  enum e_animation
    {
      ATTACK,
      SPELL,
      DEATH,
      IDLE,
      RUN
    };

  e_animation	animation;

  Graphic::Vector3f	direction;
  Graphic::Vector3f	position;
  Graphic::Vector3f	pov;

  Status();
  Status(Status const &);
  Status& operator=(Status const &);
  ~Status();
};

#endif
