#ifndef	___GRAPHIC_GUI___
#define	___GRAPHIC_GUI___

#include "GDL/Text.hpp"
#include "Graphic/GuiImage.hpp"
#include "Map/GameMap.hpp"
#include "Statistics.hpp"
#include "Character/Player.hpp"

namespace Graphic
{

  class GraphicGui
  {
    
    enum e_graphicStats
      {
	POWER,
	DEFENSE,
	CRITICAL,
	RESILIENCE,
	RANGE,
	SPEED,
	END
      };

    typedef bool	(Map::GameMap::*ptr_func)(int, int) const;
    
  public:

    GraphicGui(const Character::Player *player, float x, float y, int id, int nb_max_gui);
    ~GraphicGui();

    void	setPosition(float x, float y);
    void	draw(const Character::Player *player, Map::GameMap *map);

  private:

    GraphicGui(const GraphicGui &);
    const GraphicGui	&operator=(const GraphicGui &);
    
    void	createSquare(float x, float y, double width, double height);
    void	drawMiniMap(Map::GameMap *map, const Character::Player *player);

    GuiImage		*_skillBar;
    GuiImage		*_life;
    GuiImage		*_mana;
    GuiImage		*_avatar;

    GuiImage		*_skillImgs[2];
    GuiImage		*_inventory[3];
    gdl::Text		*_inventoryText[3];
    gdl::Text		*_skillTimeText;
    GuiImage		*_statsImgs[END];
    gdl::Text		*_statsText[END];
    gdl::Text		*_pvPmText[2];
    float		_x;
    float		_y;
    float		_scale;
    int			_id;
    int			_nb_max_gui;
    std::map<int, std::pair<ptr_func, Data::e_image> >	_minimapImgs;
  };

};

#endif
