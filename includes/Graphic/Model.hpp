//
// Ashe.hpp for Bomberman in /home/decene_a//Projets/BomberMan/Tests/Objects
// 
// Made by alexandre deceneux
// Login   <decene_a@epitech.net>
// 
// Started on  Wed May  8 05:21:18 2013 alexandre deceneux
// Last update Wed Jun  5 14:01:29 2013 alexandre deceneux
//

#ifndef	___MODEL___
#define	___MODEL___

#include "GDL/Model.hpp"
#include "Graphic/AObject.hpp"
#include "Data.hpp"

namespace Graphic
{

  class	Model : public AObject
  {

  public:

    Model(Data::e_model model);
    ~Model();

    void	initialize();
    void	update(gdl::GameClock *clock);
    void	draw(void);
    void	unload();
    bool	setAnimation(std::string animation);

  private:

    void	loadModels();

    gdl::Model			_model;
    float			_angle;
    std::vector<std::string>	_anims;
  };

}

#endif
