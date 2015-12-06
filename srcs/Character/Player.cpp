#include "Character/Player.hpp"

//
// CTOR / DTOR
//

Character::Player::Player(GameInfo &game_info, int nbr, Profile *profile,
			  Champion::Champion *champion)
  : Character(game_info, champion), _trueProfile(profile), _nbr(nbr)
{
  if (this->_trueProfile)
    this->_profile.name = this->_trueProfile->name;
}

Character::Player::~Player()
{
  this->updateTrueProfile();
  if (this->_selectedChampion)
    {
      this->_selectedChampion->reset();
      this->_selectedChampion->setSelected(false);
    }
}

//
// GETTER
//

int		Character::Player::getNbr() const
{
  return (this->_nbr);
}

Profile const	*Character::Player::getTrueProfile() const
{
  return (this->_trueProfile);
}

void		Character::Player::setTrueProfile(Profile *profile)
{
  this->_trueProfile = profile;
  if (this->_trueProfile)
    this->_profile.name = this->_trueProfile->name;
}

void	Character::Player::load(std::string const &champion, Statistics *stats, Profile *profile)
{
  Data	*data = Data::getInstance();

  for (std::list<Champion::Champion *>::iterator it = data->championsPool.begin();
       it != data->championsPool.end(); ++it)
    if ((*it)->getName() == champion)
      {
	this->_selectedChampion = *it;
	break;
      }
  this->_stats = *stats;
  this->_trueProfile = profile;
  if (profile)
    this->_profile.name = this->_trueProfile->name;
}

void	Character::Player::updateTrueProfile()
{
  Data	*data = Data::getInstance();

  data->db.saveProfile(this->_trueProfile->id,
		       this->_trueProfile->score + this->_profile.score,
		       this->_trueProfile->nbrDeaths + this->_profile.nbrDeaths,
		       this->_trueProfile->nbrBotsKilled + this->_profile.nbrBotsKilled,
		       this->_trueProfile->nbrPlayersKilled + this->_profile.nbrPlayersKilled);
}
