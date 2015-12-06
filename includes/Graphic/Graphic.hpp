#ifndef	___GRAPHIC___
#define	___GRAPHIC___

#include <vector>
#include "Graphic/Camera.hpp"
#include "Graphic/Primitive.hpp"
#include "Graphic/GraphicGui.hpp"
#include "GameInfo.hpp"
#include "Map/EItems.hpp"
#include "Data.hpp"

#define	CASE_SIZE 200

namespace Graphic
{

  class	Graphic
  {

  public:

    Graphic(int nb_max_cameras, const GameInfo &gameInfo);
    ~Graphic();

    void	draw();

    static AObject        *loadItemModel(Map::e_item item, float size = 1.0f);

  private:

    Graphic(const Graphic &);
    Graphic	&operator=(const Graphic &);

    void	set2DMode(Data *datas) const;
    void	set3DMode() const;

    void	updateModel(const Character::Character *character, Data *datas);
    void	updateItem(const Map::AEntity *item, Data *datas);
    void	drawScene(Data *datas);

    std::vector<Camera>	_cameras;
    std::vector<GraphicGui *>	_gui;
    std::vector<Primitive::Plan>	_ground;
    std::map<Status::e_animation, std::string>	_anims;
    Primitive::Sphere	_skydome;
    int			_nbrPlayers;
    const GameInfo	&_gameInfo;
  };

}

#endif
