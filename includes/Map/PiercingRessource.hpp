#ifndef __PIERCING_RESSOURCE__HPP
# define __PIERCING_RESSOURCE__HPP

# include "Map/ARessource.hpp"

namespace Map
{
  class PiercingRessource : public ARessource
  {
    PiercingRessource(PiercingRessource const &);
    PiercingRessource& operator=(PiercingRessource const &);

  public:
    PiercingRessource(int, int);
    ~PiercingRessource();

    void	useEntity(Character::Character *);
  };
};

#endif
