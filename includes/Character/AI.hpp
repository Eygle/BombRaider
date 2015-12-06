#ifndef	__AI_HPP__
# define __AI_HPP__

# include <queue>

# include "Character/Character.hpp"
# include "Character/Player.hpp"

namespace Character
{
  class	AI : public Character
  {
  public:
    struct Action
    {
      State::e_ArcadeAction	action;
      float			value;

      Action(State::e_ArcadeAction, float);
    };

  private:
    std::queue<Action>			_todo;
    std::list<Graphic::Vector3f>	_path;
    int					_difficulty;

    void		push(State::e_ArcadeAction, float);
    float		calcDistance(const Graphic::Vector3f &p1, const Graphic::Vector3f &p2) const;
    bool		isDangerousPlace(Graphic::Vector3f &start, int direction = -1, int how_far = 0) const;
    Graphic::Vector3f			findSafePlace(Graphic::Vector3f &start,
						      int from = -1,
						      int how_far = 0) const;
    Graphic::Vector3f			findClosestItem(Graphic::Vector3f &start,
							int from = -1,
							int how_far = 0) const;
    Graphic::Vector3f			findClosestChamp(Graphic::Vector3f &start);

    AI();
    AI(AI const &);
    AI &operator=(AI const &);

  public:
    AI(GameInfo &);
    ~AI();

    void		calculAction();
    Action const	&front() const;
    void		pop();
    void		load(Statistics *, int);
  };
};

#endif
