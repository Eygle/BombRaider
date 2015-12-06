#ifndef __A_ENTITY_HPP__
#define __A_ENTITY_HPP__

# include "Graphic/AObject.hpp"
# include "Statistics.hpp"
# include "Status.hpp"
# include "Map/EItems.hpp"
# include "XML/ticpp.h"

# define EXPLOSION_TIME		1

namespace Character
{
  class Character;
};

class GameInfo;

namespace Map
{
  class AEntity
  {
  private:
    AEntity(AEntity const &);
    AEntity& operator=(AEntity const &);

  protected:
    e_item		_type;
    e_category		_category;
    bool		_isBlocking;
    Status		*_prev;
    Status		*_now;
    Graphic::AObject	*_model;

  public:
    AEntity(e_item, e_category, bool, int, int);
    virtual ~AEntity();

    e_item			getType() const;
    e_category			getCategory() const;
    Graphic::AObject		*getModel() const;
    void			setModel(Graphic::AObject *);
    bool			isBlocking() const;
    Status			*getPrevStatus() const;
    Status			*getNowStatus() const;
    virtual void		update();

    virtual bool action(Character::Character *) = 0;
    virtual bool takeDmg(Statistics const &) = 0;

    virtual void	save(TiXmlElement *, GameInfo *);
  };
};

#endif
