#ifndef PROFILE_H_
# define PROFILE_H_

# include <string>

struct Profile
{
  int		id;
  std::string	name;
  int		score;
  int		nbrDeaths;
  int		nbrBotsKilled;
  int		nbrPlayersKilled;

  Profile();
  Profile(int, std::string const &, int, int, int, int);
};

#endif
