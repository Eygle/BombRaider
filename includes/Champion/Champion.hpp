#ifndef	__CHAMPION_HPP__
#define __CHAMPION_HPP__

# include <string>

# include "Graphic/GuiImage.hpp"
# include "Graphic/Model.hpp"
# include "Champion/ASkill.hpp"
# include "Statistics.hpp"

#define MODEL "ressources/models/"

namespace Champion
{
  class	Champion
  {
  protected:
    Champion();
    virtual ~Champion();

    Graphic::Image	*_avatarFull;
    Graphic::Image	*_avatarSmall;
    Graphic::Image	*_skillIcon;
    Graphic::Image	*_skillDarkIcon;
    Graphic::Model	*_model;
    Skill::ASkill	*_skill;
    Statistics		_stats;
    std::string		_name;
    bool		_selected;
    std::string		_skillTag;

  public:
    Graphic::Image		*getAvatarSmall() const;
    Graphic::Image		*getAvatarFull() const;
    Graphic::Image		*getSkillIcon() const;
    Graphic::Image		*getSkillDarkIcon() const;
    std::string	const		&getSkillTag() const;
    Graphic::Model		*getModel() const;
    Statistics const		&getStats() const;
    std::string	const		&getName() const;
    bool			isSelected() const;
    int				getSkillTimePercent() const;
    float			getSkillTimeRemain() const;

    void	setSelected(bool);

    void	setModel(Graphic::Model *);

    bool	isSkillReady() const;
    bool	isSkillActive() const;
    bool	actionSkill(Character::Character *);
    void	updateSkill(Character::Character *);

    void	reset();

  private:
    Champion(Champion const &);
    Champion	&operator=(Champion const &);
  };
};

#endif
