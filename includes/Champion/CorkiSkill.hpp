#ifndef __CORKI_SKILL__
# define __CORKI_SKILL__

# include "Champion/ASkill.hpp"

namespace Champion
{
  namespace Skill
  {
    class CorkiSkill : public ASkill
    {
      CorkiSkill(CorkiSkill const &);
      CorkiSkill& operator=(CorkiSkill const &);

    public:
      CorkiSkill();
      ~CorkiSkill();

      bool	action(Character::Character *);
      void	update(Character::Character *);
    };
  };
};

#endif
