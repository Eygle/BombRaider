#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <string>
#include "Character/Character.hpp"
#include "State/StateActions.hpp"

namespace Character
{
  class Player : public Character
  {
    Profile	*_trueProfile;
    int		_nbr;

    Player(Player const &);
    Player &operator=(Player const &);

    void		updateTrueProfile();

  public:
    ~Player();
    Player(GameInfo &, int, Profile * = 0, Champion::Champion *champion = 0);

    int			getNbr() const;
    Profile const	*getTrueProfile() const;
    void		setTrueProfile(Profile *profile);
    void		load(std::string const &, Statistics *, Profile *);
  };
};

#endif
