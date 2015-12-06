#ifndef __SCORESTATE__
#define __SCORESTATE__

#include <string>
#include "MenuState.hpp"
#include "Graphic/GuiImage.hpp"
#include "Character/Character.hpp"
#include "Menu/SimpleButton.hpp"

namespace Menu
{
  enum e_ranking
    {
      CHALLENGER = 0,
      DIAMOND,
      PLATINE,
      GOLD,
      SILVER,
      BRONZE
    };
  
  class ScoreProfil : public AButton
  {
  private:
    Graphic::ImagePosition	pos_;
    Graphic::GuiImage		medal_;
    Graphic::GuiImage		avatar_;
    std::string			name_;
    e_ranking			rank_;
  public :
    ScoreProfil(e_ranking rank, const std::string &name,Graphic::Image *image);
    ~ScoreProfil();
    
    virtual void action(char c);
    virtual void update();
    virtual void draw();    
    void setMedalPos();
  };
  
  class ScoreState : public MenuState
  {
  private:
    std::list<ScoreProfil  *> profils_;
    bool			init_;
    bool			score_;
    std::list<Character::Character *> getTop();
    Graphic::GuiImage		layout_;
    Menu::SimpleButton		*title_;
  public:
    ScoreState(bool score);
    ~ScoreState();
    virtual	void	draw();
    virtual	void	reset();
    virtual	void	update();
    void		initScore();
    void		drawProfile();
    void		initRanking();
  };
  bool compareChar(Character::Character *c1, Character::Character *c2);
};

#endif
