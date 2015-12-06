#include "Database/Database.hpp"

Database::Score::Score(std::string name, int score)
  : name(name), score(score)
{
}

Database::Database::Database()
  : _pDatabase(new Kompex::SQLiteDatabase("ressources/bomberman.db", SQLITE_OPEN_READWRITE, 0))
{
}

Database::Database::~Database()
{
  delete this->_pDatabase;
}

void	Database::Database::getLanguages(std::queue<std::string> &list) const
{
  Kompex::SQLiteStatement *pStmt = new Kompex::SQLiteStatement(this->_pDatabase);

  pStmt->Sql("SELECT name FROM languages;");
  while (pStmt->FetchRow())
    list.push(pStmt->GetColumnString(0));
  pStmt->FreeQuery();
}

Database::e_lang	Database::Database::getLanguage() const
{
  Kompex::SQLiteStatement	*pStmt = new Kompex::SQLiteStatement(this->_pDatabase);
  int	ret;

  pStmt->Sql("SELECT id_lang FROM config;");
  pStmt->FetchRow();
  ret = pStmt->GetColumnInt(0);
  pStmt->FreeQuery();

  return static_cast<e_lang>(ret);
}

int	Database::Database::getMusicVol() const
{
  Kompex::SQLiteStatement	*pStmt = new Kompex::SQLiteStatement(this->_pDatabase);
  int	ret;

  pStmt->Sql("SELECT music_vol FROM config;");
  pStmt->FetchRow();
  ret = pStmt->GetColumnInt(0);
  pStmt->FreeQuery();

  return ret;
}

int	Database::Database::getNoisesVol() const
{
  Kompex::SQLiteStatement	*pStmt = new Kompex::SQLiteStatement(this->_pDatabase);
  int	ret;

  pStmt->Sql("SELECT noises_vol FROM config;");
  pStmt->FetchRow();
  ret = pStmt->GetColumnInt(0);
  pStmt->FreeQuery();

  return ret;
}

int	Database::Database::getVoicesVol() const
{
  Kompex::SQLiteStatement	*pStmt = new Kompex::SQLiteStatement(this->_pDatabase);
  int	ret;

  pStmt->Sql("SELECT voices_vol FROM config;");
  pStmt->FetchRow();
  ret = pStmt->GetColumnInt(0);
  pStmt->FreeQuery();

  return ret;
}

bool	Database::Database::getMinimap() const
{
  Kompex::SQLiteStatement	*pStmt = new Kompex::SQLiteStatement(this->_pDatabase);
  bool	ret;

  pStmt->Sql("SELECT minimap FROM config;");
  pStmt->FetchRow();
  ret = pStmt->GetColumnBool(0);
  pStmt->FreeQuery();

  return ret;
}

void	Database::Database::setLanguage(int lang) const
{
  Kompex::SQLiteStatement	*pStmt = new Kompex::SQLiteStatement(this->_pDatabase);
  std::ostringstream		oss;

  oss << "UPDATE config SET id_lang = " << lang << ";";
  pStmt->SqlStatement(oss.str());
  pStmt->FreeQuery();
}

void	Database::Database::setMusicVol(int vol) const
{
  Kompex::SQLiteStatement	*pStmt = new Kompex::SQLiteStatement(this->_pDatabase);
  std::ostringstream		oss;

  oss << "UPDATE config SET music_vol = " << vol << ";";
  pStmt->SqlStatement(oss.str());
  pStmt->FreeQuery();
}

void	Database::Database::setNoisesVol(int vol) const
{
  Kompex::SQLiteStatement	*pStmt = new Kompex::SQLiteStatement(this->_pDatabase);
  std::ostringstream		oss;

  oss << "UPDATE config SET noises_vol = " << vol << ";";
  pStmt->SqlStatement(oss.str());
  pStmt->FreeQuery();
}

void	Database::Database::setVoicesVol(int vol) const
{
  Kompex::SQLiteStatement	*pStmt = new Kompex::SQLiteStatement(this->_pDatabase);
  std::ostringstream		oss;

  oss << "UPDATE config SET voices_vol = " << vol << ";";
  pStmt->SqlStatement(oss.str());
  pStmt->FreeQuery();
}

void	Database::Database::setMinimap(bool map) const
{
  Kompex::SQLiteStatement	*pStmt = new Kompex::SQLiteStatement(this->_pDatabase);
  std::ostringstream		oss;

  oss << "UPDATE config SET minimap = " << map << ";";
  pStmt->SqlStatement(oss.str());
  pStmt->FreeQuery();
}

std::string Database::Database::getText(e_lang lang, std::string const &tag) const
{
  Kompex::SQLiteStatement	*pStmt = new Kompex::SQLiteStatement(this->_pDatabase);
  std::ostringstream		oss;

  oss << "SELECT text FROM texts WHERE id_lang = " << lang << " AND tag LIKE \"" << tag << "\" LIMIT 1;";
  pStmt->Sql(oss.str());
  pStmt->FetchRow();
  std::string text = pStmt->GetColumnString(0);
  pStmt->FreeQuery();
  return text;
}

void	Database::Database::getScores(std::list<Score *> &list, int nbr, int page) const
{
  Kompex::SQLiteStatement	*pStmt = new Kompex::SQLiteStatement(this->_pDatabase);
  std::ostringstream		oss;

  oss << "SELECT name, score FROM profiles ORDER BY score DESC LIMIT " << (nbr * (page - 1)) << "," << nbr << ";";
  pStmt->Sql(oss.str());
  while (pStmt->FetchRow())
    list.push_back(new Score(pStmt->GetColumnString(0), pStmt->GetColumnInt(1)));
  pStmt->FreeQuery();
}

int	Database::Database::getTotalScores() const
{
  Kompex::SQLiteStatement       *pStmt = new Kompex::SQLiteStatement(this->_pDatabase);

  pStmt->Sql("SELECT COUNT(*) FROM scores;");
  pStmt->FetchRow();

  int	val = pStmt->GetColumnInt(0);

  pStmt->FreeQuery();
  return val;
}

Profile	*Database::Database::getProfile(std::string const &name) const
{
  Kompex::SQLiteStatement       *pStmt = new Kompex::SQLiteStatement(this->_pDatabase);
  std::ostringstream		oss;
  Profile			*ret = new Profile;

  oss << "SELECT COUNT(*) FROM profiles WHERE name LIKE \"" << name << "\" LIMIT 1;";
  pStmt->Sql(oss.str());
  pStmt->FetchRow();
  if (pStmt->GetColumnInt(0))
    {
      oss.str("");
      oss << "SELECT id, name, score, nbrDeaths, nbrBotsKilled, nbrPlayersKilled";
      oss << " FROM profiles WHERE name LIKE \"" << name << "\" LIMIT 1;";
      pStmt->Sql(oss.str());
      pStmt->FetchRow();
      ret->id = pStmt->GetColumnInt(0);
      ret->name = pStmt->GetColumnString(1);
      ret->score = pStmt->GetColumnInt(2);
      ret->nbrDeaths = pStmt->GetColumnInt(3);
      ret->nbrBotsKilled = pStmt->GetColumnInt(4);
      ret->nbrPlayersKilled = pStmt->GetColumnInt(5);
    }
  else
    {
      oss.str("");
      oss << "INSERT INTO profiles(name, score, nbrDeaths, nbrBotsKilled,";
      oss << " nbrPlayersKilled) VALUES(\"" << name << "\", 0, 0, 0, 0);";
      pStmt->SqlStatement(oss.str());
      oss.str("");
      oss << "SELECT id, name FROM profiles WHERE name LIKE \"" << name << "\" LIMIT 1;";
      pStmt->Sql(oss.str());
      pStmt->FetchRow();
      ret->id = pStmt->GetColumnInt(0);
      ret->name = pStmt->GetColumnString(1);
      ret->score = 0;
      ret->nbrDeaths = 0;
      ret->nbrBotsKilled = 0;
      ret->nbrPlayersKilled = 0;
    }

  pStmt->FreeQuery();

  return ret;
}

Profile	*Database::Database::getProfile(int id) const
{
  Kompex::SQLiteStatement       *pStmt = new Kompex::SQLiteStatement(this->_pDatabase);
  std::ostringstream		oss;
  Profile			*ret = new Profile;

  oss << "SELECT COUNT(*) FROM profiles WHERE id = " << id << " LIMIT 1;";
  pStmt->Sql(oss.str());
  pStmt->FetchRow();
  if (pStmt->GetColumnInt(0))
    {
      oss.str("");
      oss << "SELECT id, name, score, nbrDeaths, nbrBotsKilled, nbrPlayersKilled";
      oss << " FROM profiles WHERE id = " << id << " LIMIT 1;";
      pStmt->Sql(oss.str());
      pStmt->FetchRow();
      ret->id = pStmt->GetColumnInt(0);
      ret->name = pStmt->GetColumnString(1);
      ret->score = pStmt->GetColumnInt(2);
      ret->nbrDeaths = pStmt->GetColumnInt(3);
      ret->nbrBotsKilled = pStmt->GetColumnInt(4);
      ret->nbrPlayersKilled = pStmt->GetColumnInt(5);
    }
  else
    {
      ret->id = 0;
      ret->name = "DEFAULT";
      ret->score = 0;
      ret->nbrDeaths = 0;
      ret->nbrBotsKilled = 0;
      ret->nbrPlayersKilled = 0;
    }

  pStmt->FreeQuery();

  return ret;
}

void	Database::Database::saveProfile(int id, int s, int d, int bK, int pK) const
{
  Kompex::SQLiteStatement       *pStmt = new Kompex::SQLiteStatement(this->_pDatabase);
  std::ostringstream	oss;

  oss << "UPDATE profiles SET score = " << s << ", nbrDeaths = " << d;
  oss << ", nbrBotsKilled = " << bK << ", nbrPlayersKilled = " << pK << " WHERE id = " << id;
  pStmt->SqlStatement(oss.str());

  pStmt->FreeQuery();
}

void	Database::Database::getKeys(std::list<Keys *> &list) const
{
  Kompex::SQLiteStatement       *pStmt = new Kompex::SQLiteStatement(this->_pDatabase);

  pStmt->Sql("SELECT id, key, action FROM keys_binds;");
  while (pStmt->FetchRow())
    {
      Keys		*key = new Keys;

      key->id = pStmt->GetColumnInt(0);
      key->key = pStmt->GetColumnInt(1);
      key->action = pStmt->GetColumnInt(2);
      list.push_back(key);
    }
  pStmt->FreeQuery();
}

int	Database::Database::getKey(int id, int action) const
{
  Kompex::SQLiteStatement       *pStmt = new Kompex::SQLiteStatement(this->_pDatabase);
  std::ostringstream		oss;
  int				ret;

  oss << "SELECT key FROM keys_binds WHERE id = " << id << " AND action = " << action;
  oss << " LIMIT 1;";
  pStmt->Sql(oss.str());
  pStmt->FetchRow();
  ret = pStmt->GetColumnInt(0);
  pStmt->FreeQuery();

  return ret;
}

int	Database::Database::getPlayerController(int playerId) const
{
  Kompex::SQLiteStatement       *pStmt = new Kompex::SQLiteStatement(this->_pDatabase);
  std::ostringstream		oss;
  int				ret;

  oss << "SELECT controller FROM players_controllers WHERE player_id = "<< playerId << " LIMIT 1;";
  pStmt->Sql(oss.str());
  pStmt->FetchRow();
  ret = pStmt->GetColumnInt(0);
  pStmt->FreeQuery();

  return ret;
}

void	Database::Database::setPlayerController(int player, int controller) const
{
  Kompex::SQLiteStatement       *pStmt = new Kompex::SQLiteStatement(this->_pDatabase);
  std::ostringstream		oss;

  oss << "UPDATE players_controllers SET controller = " << controller << " WHERE player_id = " << player;
  pStmt->SqlStatement(oss.str());
  pStmt->FreeQuery();
}

void	Database::Database::setKey(int id, int action, int key) const
{
  Kompex::SQLiteStatement       *pStmt = new Kompex::SQLiteStatement(this->_pDatabase);
  std::ostringstream		oss;

  oss << "UPDATE keys_binds SET key = " << key << " WHERE id = " << id;
  oss << " AND action = " << action;
  pStmt->SqlStatement(oss.str());
  pStmt->FreeQuery();
}

void	Database::Database::getModel(Model &model, std::string const &name) const
{
  Kompex::SQLiteStatement       *pStmt = new Kompex::SQLiteStatement(this->_pDatabase);
  std::ostringstream		oss;

  oss << "SELECT path, end_idle, end_run, end_attack, end_spell, end_death, direction";
  oss << " FROM models WHERE name LIKE \"" << name << "\" LIMIT 1;";
  pStmt->Sql(oss.str());
  pStmt->FetchRow();

  model.path = pStmt->GetColumnString(0);
  model.end_idle = pStmt->GetColumnInt(1);
  model.end_run = pStmt->GetColumnInt(2);
  model.end_attack = pStmt->GetColumnInt(3);
  model.end_spell = pStmt->GetColumnInt(4);
  model.end_death = pStmt->GetColumnInt(5);
  model.direction = pStmt->GetColumnInt(6);
  pStmt->FreeQuery();
}

void	Database::Database::listChampions(std::list<std::pair<int, std::string> * > &list, int nbr, int page) const
{
  Kompex::SQLiteStatement       *pStmt = new Kompex::SQLiteStatement(this->_pDatabase);
  std::ostringstream oss;

  oss << "SELECT id, name FROM champions LIMIT " << (nbr * (page - 1)) << ", " << nbr;
  pStmt->Sql(oss.str());

  while (pStmt->FetchRow())
    list.push_back(new std::pair<int, std::string>(pStmt->GetColumnInt(0), pStmt->GetColumnString(1)));

  pStmt->FreeQuery();
}

Statistics	*Database::Database::getChampionStats(int id) const
{
  Kompex::SQLiteStatement       *pStmt = new Kompex::SQLiteStatement(this->_pDatabase);
  Statistics			*stats;
  std::ostringstream		oss;

  oss << "SELECT hp, mana, critical, defence, power, range, resilience FROM champions WHERE id = "
      << id << "LIMIT 1;";
  pStmt->Sql(oss.str());
  pStmt->FetchRow();

  stats = new Statistics(pStmt->GetColumnInt(2), pStmt->GetColumnInt(3), pStmt->GetColumnInt(0),
			 pStmt->GetColumnInt(0), pStmt->GetColumnInt(1), pStmt->GetColumnInt(1),
			 pStmt->GetColumnInt(4), pStmt->GetColumnInt(5), pStmt->GetColumnInt(6));

  pStmt->FreeQuery();
  return stats;
}

void	Database::Database::getAllSounds(std::list<Sounds *> &list) const
{
  Kompex::SQLiteStatement       *pStmt = new Kompex::SQLiteStatement(this->_pDatabase);

  pStmt->Sql("SELECT id, path, category, loop FROM sounds;");
  while (pStmt->FetchRow())
    {
      Sounds *sound = new Sounds;
      sound->id = pStmt->GetColumnInt(0);
      sound->path = pStmt->GetColumnString(1);
      sound->soundType = pStmt->GetColumnInt(2);
      sound->loop = pStmt->GetColumnBool(3);
      list.push_back(sound);
    }
  pStmt->FreeQuery();
}
