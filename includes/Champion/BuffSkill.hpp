#ifndef __BUFF_SKILL_HPP__
# define __BUFF_SKILL_HPP__

# include "Champion/ASkill.hpp"

namespace Champion
{
  namespace Skill
  {
    class BuffSkill : public ASkill
    {
    public:
      BuffSkill(Statistics const &, int, float, float);
      ~BuffSkill();

      bool	action(Character::Character *);
      void	update(Character::Character *);

    private:
      Statistics	_skillStats;

      BuffSkill();
      BuffSkill(BuffSkill const &);
      BuffSkill &operator=(BuffSkill const &);
    };
  };
};

#endif
