#ifndef IDATABASE_H_
# define IDATABASE_H_

# include <string>
# include <list>
# include <queue>
# include <utility>

# include "Profile.hpp"
# include "Statistics.hpp"

namespace Database
{
  enum e_lang
    {
      FRENCH = 1,
      ENGLISH
    };

  struct Score
  {
    Score(std::string, int);

    std::string	name;
    int		score;
  };

  struct Keys
  {
    int	key;
    int	id;
    int	action;
  };

  struct Model
  {
    std::string	path;
    int		end_idle;
    int		end_run;
    int		end_attack;
    int		end_spell;
    int		end_death;
    float	direction;
  };

  struct Sounds
  {
    int		id;
    std::string path;
    int		soundType;
    bool	loop;

  };

  class IDatabase
  {
  public:
    IDatabase() {}
    virtual ~IDatabase() {}

    virtual void	getLanguages(std::queue<std::string> &) const = 0;
    virtual e_lang	getLanguage() const = 0;
    virtual int		getMusicVol() const = 0;
    virtual int		getNoisesVol() const = 0;
    virtual int		getVoicesVol() const = 0;
    virtual bool	getMinimap() const = 0;
    virtual void	setLanguage(int) const = 0;
    virtual void	setMusicVol(int) const = 0;
    virtual void	setNoisesVol(int) const = 0;
    virtual void	setVoicesVol(int) const = 0;
    virtual void	setMinimap(bool) const = 0;
    virtual std::string	getText(e_lang, std::string const &) const = 0;
    virtual void	getScores(std::list<Score *> &, int, int) const = 0;
    virtual int		getTotalScores() const = 0;
    virtual Profile	*getProfile(std::string const &) const = 0;
    virtual Profile	*getProfile(int) const = 0;
    virtual void	saveProfile(int, int, int, int, int) const = 0;
    virtual void	getKeys(std::list<Keys *> &) const = 0;
    virtual int		getKey(int, int) const = 0;
    virtual int		getPlayerController(int) const = 0;
    virtual void	setPlayerController(int, int) const = 0;
    virtual void	setKey(int, int, int) const = 0;
    virtual void	getModel(Model &, std::string const &) const = 0;
    virtual void	listChampions(std::list<std::pair<int, std::string> * > &, int, int) const = 0;
    virtual Statistics	*getChampionStats(int) const = 0;
    virtual void	getAllSounds(std::list<Sounds *> &) const = 0;
  };
};

#endif
