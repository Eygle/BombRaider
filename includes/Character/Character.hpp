#ifndef __ACHARACTER_HPP__
#define __ACHARACTER_HPP__

#include <vector>

#include "GDL/GameClock.hpp"
#include "Status.hpp"
#include "State/StateActions.hpp"
#include "Character/ICharacter.hpp"
#include "Champion/Champion.hpp"
#include "Graphic/Vector3f.hpp"
#include "Map/ARessource.hpp"
#include "Clock/Clock.hpp"
#include "Profile.hpp"

#define	INVUL_TIME 3
#define SPEED_CTE 500
#define TURN_SPEED_CTE 10
#define CLASSIC_BOMB_MANA 10

namespace Map
{
  class ABomb;
};

struct GameInfo;

namespace Character
{
  class Character : public ICharacter
  {
  public:

    enum characterType
      {
	PLAYER,
	AI
      };

    Champion::Champion			*getChampion() const;
    Status				*getPrevState() const;
    Status				*getNowState() const;
    characterType			getType() const;
    std::vector<Map::ARessource *> const	&getInventory() const;
    GameInfo				&getGameInfo() const;
    Statistics const			&getAllStats() const;
    int					getStat(Statistics::e_stat) const;
    int					getId() const;
    Profile				&getProfile();
    Statistics::e_gauge_statut		setStat(Statistics::e_stat, int);
    void				setChampion(Champion::Champion *);

  public:
    void	resetInvulnerability();
    bool	takeItem(Map::ARessource *);
    bool	dropBomb(Map::ABomb *, int, bool = true);
    void	addStats(Statistics const &);
    void	subStats(Statistics const &);
    bool	takeDmg(Statistics const &);
    void	checkCase();
    bool	isDead();
    void	action(State::e_ArcadeAction, float);
    void	update();
    void	setClock(Clock *);
    Clock	*getClock();

    virtual ~Character();

  protected:
    typedef void (Character::*func_action)(float);

    GameInfo				&_gameInfo;
    std::vector<Map::ARessource *>	_inventory;
    Status				*_stateNow;
    Status				*_statePrev;
    Champion::Champion			*_selectedChampion;
    Statistics				_stats;
    Profile				_profile;
    gdl::Clock				_invulnerability;
    gdl::Clock				_manaClock;
    int					_id;
    func_action				_actions[State::LAST_ARCADE_ACTION];
    characterType			_type;
    Clock				*_globalClock;

    void	move(float);
    void	turn(float);    

    Character(GameInfo &, Champion::Champion * = 0);

  private:
    Character();
    Character(Character const &);
    Character &operator=(Character const &);

    std::map<std::string, Sound::e_sound>	_mapSound;

    void	joystick(float);
    void	setJoystickCamera(float);
    void	dropClassicalBomb(float);
    void	moveOnMap(const Graphic::Vector3f &);
    bool	isThereCollisionAround(float);
    void	skill(float);
    void	idle(float);
    void	slot1(float);
    void	slot2(float);
    void	slot3(float);
    void	slot(int);
  };
};

#endif
