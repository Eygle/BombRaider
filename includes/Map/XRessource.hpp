#ifndef __X_RESSOURCE__HPP
# define __X_RESSOURCE__HPP

# include "Map/ARessource.hpp"

namespace Map
{
  class XRessource : public ARessource
  {
    XRessource(XRessource const &);
    XRessource& operator=(XRessource const &);

  public:
    XRessource(int, int);
    ~XRessource();

    void	useEntity(Character::Character *);
  };
};

#endif
