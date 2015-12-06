#ifndef __CHOGATH_SKILL__
#define __CHOGATH_SKILL__

#include "Champion/ASkill.hpp"
#include "Character/Character.hpp"

namespace Champion
{
  namespace Skill
  {
    class ChogathSkill : public ASkill
    {
      ChogathSkill(ChogathSkill const &);
      ChogathSkill& operator=(ChogathSkill const &);
      void inflictDmg(int, int, Character::Character const *);

    public:
      ChogathSkill();
      ~ChogathSkill();

      bool	action(Character::Character *);
      void	update(Character::Character *);
    };
  };
};

#endif
