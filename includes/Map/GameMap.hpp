#ifndef __GAME_MAP_HPP__
# define __GAME_MAP_HPP__

# include <vector>

# include "Map/MapCase.hpp"

# define BOX_ABUNDANCE	70

class GameInfo;

namespace Map
{
  class GameMap
  {
    int	_height;
    int	_width;

    std::vector<std::vector<MapCase> >	_map;

    typedef void (GameMap::*createFunc)(int, int);

    createFunc	_boxCreator[3];

    void	createClassicBox(int, int);
    void	createIronBox(int, int);
    void	createUltimaBox(int, int);
    void	createRandomBox(int, int);

    bool	isThereSomeoneAround(int, int, GameInfo const &);
    bool	isItAround(Character::Character const *, int, int);

    GameMap();
    GameMap(GameMap const &);
    GameMap& operator=(GameMap const &);

  public:
    GameMap(int, int);
    ~GameMap();

    int		getHeight() const;
    int		getWidth() const;
    MapCase	&at(int, int);

    bool	isWallAt(int, int) const;
    void	updateMap();
    int		isPlayerAt(int, int, const Character::Character * = 0) const;
    bool	isPlayerAliveAt(int, int) const;
    bool	isBoxAt(int, int) const;
    bool	isBombAt(int, int) const;
    bool	isBonusAt(int, int) const;
    bool	isExplodingAt(int, int) const;

    void	generate(GameInfo const &);

    std::vector<MapCase>	&operator[](int);
  };
};

#endif
