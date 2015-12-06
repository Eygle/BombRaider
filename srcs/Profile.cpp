#include "Profile.hpp"

Profile::Profile(int myId, std::string const &myName, int myScore,
		 int deaths, int nbrBotsKills, int nbrPlayersKills)
  : id(myId), name(myName), score(myScore), nbrDeaths(deaths),
    nbrBotsKilled(nbrBotsKills), nbrPlayersKilled(nbrPlayersKills)
{
}

Profile::Profile() :
score(0)
{
}
