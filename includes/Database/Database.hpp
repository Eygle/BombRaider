#ifndef DATABASE_H_
# define DATABASE_H_

# include <sstream>

# include "KompexSQLiteStatement.h"
# include "KompexSQLiteDatabase.h"

# include "Database/IDatabase.hpp"
# include "Profile.hpp"

namespace Database
{
  class Database : public IDatabase
  {
  public:
    Database();
    ~Database();

    void	getLanguages(std::queue<std::string> &) const;
    e_lang	getLanguage() const;
    int		getMusicVol() const;
    int		getNoisesVol() const;
    int		getVoicesVol() const;
    bool	getMinimap() const;
    void        setLanguage(int) const;
    void	setMusicVol(int) const;
    void	setNoisesVol(int) const;
    void	setVoicesVol(int) const;
    void	setMinimap(bool) const;
    std::string	getText(e_lang, std::string const &) const;
    void	getScores(std::list<Score *> &, int, int) const;
    int		getTotalScores() const;
    Profile	*getProfile(std::string const &) const;
    Profile	*getProfile(int) const;
    void	saveProfile(int, int, int, int, int) const;
    void	getKeys(std::list<Keys *> &) const;
    int		getKey(int, int) const;
    int		getPlayerController(int) const;
    void	setPlayerController(int, int) const;
    void	setKey(int, int, int) const;
    void	getModel(Model &, std::string const &) const;
    void	listChampions(std::list<std::pair<int, std::string> * > &, int, int) const;
    Statistics	*getChampionStats(int) const;
    void	getAllSounds(std::list<Sounds *> &) const;

  private:
    Kompex::SQLiteDatabase	*_pDatabase;
  };
};

#endif
