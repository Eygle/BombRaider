#ifndef __A_RESSOURCE_HPP__
# define __A_RESSOURCE_HPP__

# include "Map/AEntity.hpp"
# include "Map/EItems.hpp"
# include "Graphic/GuiImage.hpp"

namespace Map
{
  class ARessource : public AEntity
  {
  private:
    ARessource(ARessource const &);
    ARessource& operator=(ARessource const &);

  protected:
    int			_quantity;
    Graphic::Image	*_icon;
    bool		_isAscending;

  public:
    ARessource(Map::e_item, int, int);
    virtual ~ARessource();

    Graphic::Image  	*getIcon() const;
    int			getQuantity() const;

    bool	action(Character::Character *);
    bool	takeDmg(Statistics const &);
    void	add(int);
    virtual void	update();

    virtual void	useEntity(Character::Character *) = 0;
  };
};

#endif
