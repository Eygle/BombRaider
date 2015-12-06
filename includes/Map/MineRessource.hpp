#ifndef __MINE_RESSOURCE__HPP
# define __MINE_RESSOURCE__HPP

# include "Map/ARessource.hpp"

namespace Map
{
  class MineRessource : public ARessource
  {
    MineRessource(MineRessource const &);
    MineRessource& operator=(MineRessource const &);

  public:
    MineRessource(int, int);
    ~MineRessource();

    void	useEntity(Character::Character *);
  };
};

#endif
