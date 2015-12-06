#include "Status.hpp"

Status::Status()
  : animation(Status::IDLE)
{
}

Status::Status(Status const &other)
  : animation(other.animation), direction(other.direction),
    position(other.position), pov(other.pov)
{
}

Status& Status::operator=(Status const &other)
{
  if (this != &other)
    {
      this->animation = other.animation;
      this->direction = other.direction;
      this->position = other.position;
      this->pov = other.pov;
    }
  return (*this);
}

Status::~Status()
{
}
