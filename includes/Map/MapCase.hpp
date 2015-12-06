#ifndef __MAP_CASE_HPP__
# define __MAP_CASE_HPP__

# include <list>

# include "Statistics.hpp"
# include "Map/Explosion.hpp"

namespace Character
{
  class Character;
  class Player;
};

namespace Map
{
  class AEntity;

  class MapCase
  {
    bool	_isExploding;
    bool	_isBlocked;

    std::list<Character::Character *>	_characters;
    std::list<AEntity *>		_items;

    typedef	void (MapCase::*addFunc)(int, int);
    addFunc	_bonusCreator[18];

    void	initBonusCreator();
    void	createBonus(int, int);
    void	addManaMaxBuff(int, int);
    void	addLifeMaxBuff(int, int);
    void	addManaPotion(int, int);
    void	addLifePotion(int, int);
    void	addPowerBuff(int, int);
    void	addRangeBuff(int, int);
    void	addCriticalBuff(int, int);
    void	addDefenseBuff(int, int);
    void	addResilienceBuff(int, int);
    void	addSpeedBuff(int, int);
    void	addMissileRessource(int, int);
    void	addRebonRessource(int, int);
    void	addPiercingRessource(int, int);
    void	addMineRessource(int, int);
    void	addXRessource(int, int);
    void	addFufuRessource(int, int);
    void	addBrainRessource(int, int);
    void	createRessource(int, int);

    void	eraseItem(std::list<AEntity *>::iterator &);

  public:
    MapCase();
    MapCase(MapCase const &);
    MapCase& operator=(MapCase const &);
    ~MapCase();

    bool	isExploding() const;
    bool	isBlocked() const;
    bool	isCategory(e_category) const;
    int		isPlayer(const Character::Character * = 0) const;
    bool	isPlayerAlive() const;
    bool	isOtherPlayer(Character::Character const *) const;
    bool	isRealPlayer(std::vector<Character::Player *> const &) const;
    void	updateItems();

    std::list<AEntity *> &getItems();
    std::list<Character::Character *> &getCharacters();

    void	extinguish();
    void	explode(Explosion *);
    void	useItems(Character::Character *);

    void	addCharacter(Character::Character *);
    void	removeCharacter(Character::Character *);
    bool	addItem(AEntity *);
    void	removeItem(AEntity *);
    void	clearItems();
  };
};

#endif
