#ifndef	__STATISTICS_HPP_
#define __STATISTICS_HPP_

class	Statistics
{
public:
  enum e_stat
    {
      CRITICAL,
      DEFENSE,
      HP_MAX,
      HP,
      MANA_MAX,
      MANA,
      POWER,
      RANGE,
      RESILIENCE,
      SPEED,
      LAST
    };

  enum e_gauge_statut
    {
      EMPTY,
      FULL,
      GOOD
    };

  Statistics(int crit = 0, int def = 0, int hp = 0, int hp_max = 0, int mana = 0,
	     int mana_max = 0, int power = 0, int range = 0, int resi = 0, int speed = 0);
  Statistics(int *stat);
  Statistics(Statistics const &other);
  Statistics &operator=(Statistics const &other);
  ~Statistics();

  e_gauge_statut	add(e_stat to_change, int to_add);
  e_gauge_statut	add(Statistics const &);
  e_gauge_statut	sub(e_stat to_change, int to_sub);
  e_gauge_statut	sub(Statistics const &);
  int			get(e_stat to_get) const;

  Statistics &operator+=(Statistics const &);
  Statistics &operator-=(Statistics const &);

private:
  int	*_stats;

  e_gauge_statut checkLimit(e_stat, e_stat);
};

#endif
