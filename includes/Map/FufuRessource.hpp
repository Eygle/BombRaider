#ifndef __FUFU_RESSOURCE__HPP
# define __FUFU_RESSOURCE__HPP

# include <map>

# include "Data.hpp"
# include "Map/ARessource.hpp"

namespace Map
{
  class FufuRessource : public ARessource
  {
    FufuRessource(FufuRessource const &);
    FufuRessource& operator=(FufuRessource const &);

    std::map<std::string, Sound::e_sound>	mapSound_;

  public:
    FufuRessource(int, int);
    ~FufuRessource();

    void	useEntity(Character::Character *);
  };
};

#endif
