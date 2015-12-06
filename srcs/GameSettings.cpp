#include "GameSettings.hpp"

GameSettings::GameSettings()
  : bonusFrequency(66), boxFrequency(70), screenHeight(768), screenWidth(1366),
    nbrPlayers(1), minimap(true), difficulty(1), language(Database::ENGLISH),
    mapHeight(15), mapWidth(15)
{
}

void	GameSettings::init(bool minimap, Database::e_lang lang)
{
  this->minimap = minimap;
  this->language = lang;
}
