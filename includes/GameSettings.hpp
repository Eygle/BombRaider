#ifndef GAMESETTINGS_H_
# define GAMESETTINGS_H_

#include "Database/IDatabase.hpp"

struct GameSettings
{
  int			bonusFrequency;
  int			boxFrequency;
  int			screenHeight;
  int			screenWidth;
  int			nbrPlayers;
  int			nbrAI;
  bool			minimap;
  int			difficulty;
  Database::e_lang	language;
  int			mapHeight;
  int			mapWidth;

  GameSettings();

  void	init(bool, Database::e_lang);
};

#endif
