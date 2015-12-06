#ifndef __MISSILE_RESSOURCE__HPP
# define __MISSILE_RESSOURCE__HPP

# include "Map/ARessource.hpp"

namespace Map
{
  class MissileRessource : public ARessource
  {
    MissileRessource(MissileRessource const &);
    MissileRessource& operator=(MissileRessource const &);

  public:
    MissileRessource(int, int);
    ~MissileRessource();

    void	useEntity(Character::Character *);
  };
};

#endif
