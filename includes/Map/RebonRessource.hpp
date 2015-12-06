#ifndef __REBON_RESSOURCE__HPP
# define __REBON_RESSOURCE__HPP

# include "Map/ARessource.hpp"

namespace Map
{
  class RebonRessource : public ARessource
  {
    RebonRessource(RebonRessource const &);
    RebonRessource& operator=(RebonRessource const &);

  public:
    RebonRessource(int, int);
    ~RebonRessource();

    void	useEntity(Character::Character *);
  };
};

#endif
