#ifndef SELECTPLAYER_H_
# define SELECTPLAYER_H_

# include <GDL/Text.hpp>
# include <GDL/Image.hpp>

# include "Data.hpp"
# include "Menu/MenuState.hpp"
# include "State/AState.hpp"
# include "Menu/SelectPlayerButton.hpp"

namespace Character
{
  class Player;
};

namespace Menu
{
  enum e_Stats_Max
    {
      STATS_PV_MAX = 150,
      STATS_MANA_MAX = 25,
      STATS_POWER_MAX = 30,
      STATS_DEF_MAX = 20,
      STATS_CRIT_MAX = 20,
      STATS_RESI_MAX = 10,
      STATS_RANGE_MAX = 3,
      STATS_SPEED_MAX = 10
    };

  class SelectPlayer : public MenuState
  {
  public:
    SelectPlayer(State::e_State);
    ~SelectPlayer();

    void	update();
    void	draw();
    void	reload();

  private:
    State::e_State	id_;
    bool		init_;

    SelectPlayerButton *next_;

    void	(SelectPlayer::*funPtr[4])();

    Graphic::ImagePosition	imgPos_;
    Graphic::GuiImage		*championImg_;
    Graphic::GuiImage		*allSkillIcons_;
    Graphic::GuiImage		*skillIcon_;
    Graphic::GuiImage		*shadow_;
    Graphic::GuiImage		*shadowText1_;
    Graphic::GuiImage		*shadowText2_;

    Graphic::GuiImage		*hpBar_;
    Graphic::GuiImage		*manaBar_;
    Graphic::GuiImage		*critBar_;
    Graphic::GuiImage		*resiBar_;
    Graphic::GuiImage		*powerBar_;
    Graphic::GuiImage		*defBar_;
    Graphic::GuiImage		*rangeBar_;
    Graphic::GuiImage		*speedBar_;

    Graphic::GuiImage		*profileBackground_;

    gdl::Text	profileName_;

    gdl::Text	hpTitle_;
    gdl::Text	manaTitle_;
    gdl::Text	critTitle_;
    gdl::Text	resiTitle_;
    gdl::Text	powerTitle_;
    gdl::Text	defTitle_;
    gdl::Text	rangeTitle_;
    gdl::Text	speedTitle_;

    gdl::Text	hp_;
    gdl::Text	mana_;
    gdl::Text	crit_;
    gdl::Text	resi_;
    gdl::Text	power_;
    gdl::Text	def_;
    gdl::Text	range_;
    gdl::Text	speed_;
    gdl::Text	skill_;

    std::list<Champion::Champion *>::iterator	champion;


    void	placePlayer(Data *datas);
    void	placeAI(Data *datas);

    void	initArrow(AButton *, int, int, int, int);
    void	updateTextFromInt(gdl::Text &, int);
    void	updateTexts();
    void	updateStats();
    void	updateChampion();
    void	nextPlayer();
    void	prevPlayer();
    void	saveAndNext();
    void	reset();
    void	goBack();
    std::string	formatSkillText(std::string &);

    void	initSelectPlayer();

    SelectPlayer(SelectPlayer const &);
    SelectPlayer &operator=(SelectPlayer const &);
  };
};

#endif
