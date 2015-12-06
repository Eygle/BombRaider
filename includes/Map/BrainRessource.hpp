#ifndef __BRAIN_RESSOURCE__HPP
#define __BRAIN_RESSOURCE__HPP

# include "Map/ARessource.hpp"

namespace Map
{
  class BrainRessource : public ARessource
  {
    BrainRessource(BrainRessource const &);
    BrainRessource& operator=(BrainRessource const &);

  public:
    BrainRessource(int, int);
    ~BrainRessource();

    void	useEntity(Character::Character *);
  };
};

#endif
