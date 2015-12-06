#ifndef	__A_SKILL_HPP__
#define __A_SKILL_HPP__

# include "GDL/Clock.hpp"
# include "Statistics.hpp"
# include "Map/ClassicBomb.hpp"

namespace Character
{
  class Character;
};

namespace Champion
{
  namespace Skill
  {
    class ASkill
    {
    public:
      ASkill(int, float, float);
      virtual ~ASkill();

      bool		isActive() const;
      bool		isReady() const;
      float		getTimeRemain() const;
      int		getTimePercent() const;
      virtual bool	action(Character::Character *) = 0;
      virtual void	update(Character::Character *) = 0;

      void		reset();

    protected:
      float		_duration;
      float		_cooldown;
      int		_manaConso;
      bool		_isUsed;
      bool		_isReady;
      gdl::Clock	_skillDuration;
      gdl::Clock	_skillCooldown;

    private:
      ASkill();
      ASkill(ASkill const &);
      ASkill &operator=(ASkill const &);
    };
  };
};

#endif
