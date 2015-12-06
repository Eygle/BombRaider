#include "Graphic/Graphic.hpp"
#include "Graphic/Model.hpp"
#include "Character/Character.hpp"
#include "Character/Player.hpp"
#include "Character/AI.hpp"
#include "Map/AEntity.hpp"

Graphic::Graphic::Graphic(int nb_max_cameras, const GameInfo &gameInfo):
  _gameInfo(gameInfo)
{
  Data	*datas = Data::getInstance();

  for (int x = -2 ; x <  gameInfo.map->getWidth() + 2; x++)
    for (int y = -2 ; y < gameInfo.map->getHeight() + 2; y++)
      {
	this->_ground.push_back(Primitive::Plan(CASE_SIZE, CASE_SIZE, &datas->imgs[Data::GROUND]));
	this->_ground.back().setPos(Vector3f(x * CASE_SIZE, 0, y * CASE_SIZE));
      }
  for (int i = 0; i < nb_max_cameras; i++)
    {
      this->_gui.insert(this->_gui.begin(), new GraphicGui(gameInfo.players[i],
							   datas->gameSettings.screenWidth - 624,
							   datas->gameSettings.screenHeight - 195,
							   nb_max_cameras - i - 1, nb_max_cameras));
      this->_cameras.insert(this->_cameras.begin(), Camera(nb_max_cameras - i - 1, nb_max_cameras));
      this->_cameras.front().follow(gameInfo.players[i]->getChampion()->getModel(), CASE_SIZE * 2.2);
    }
  this->_skydome = Primitive::Sphere(1, &datas->imgs[Data::SKYDOME]);
  this->_skydome.setRadius(100 * CASE_SIZE);
  this->_skydome.setPos(Vector3f(gameInfo.map->getWidth() * CASE_SIZE / 2.0, 0, gameInfo.map->getHeight() * CASE_SIZE / 2.0));
  this->_anims[Status::IDLE] = "Idle";
  this->_anims[Status::RUN] = "Run";
  this->_anims[Status::ATTACK] = "Attack";
  this->_anims[Status::SPELL] = "Spell";
  this->_anims[Status::DEATH] = "Death";
  this->_nbrPlayers = nb_max_cameras;
}

Graphic::Graphic::~Graphic()
{
  this->_cameras.clear();
  for (std::vector<GraphicGui *>::iterator gui = this->_gui.begin();
       gui != this->_gui.end();
       gui++)
    delete (*gui);
}

void	Graphic::Graphic::updateModel(const Character::Character *character, Data *datas)
{
  Model		*model;
  Status	*status[2];

  if (!character)
    return;
  status[0] = character->getPrevState();
  status[1] = character->getNowState();
  if (!status[0] || !status[1])
    return;
  model = character->getChampion()->getModel();
  model->setPos(status[1]->position * CASE_SIZE);
  model->setRot(status[1]->direction);
  if (status[0]->animation != status[1]->animation)
    if (!model->setAnimation(this->_anims[status[1]->animation]))
      status[1]->animation = status[0]->animation;
  if (datas->gameClock)
    model->update(datas->gameClock);
  model->draw();
}

void	Graphic::Graphic::updateItem(const Map::AEntity *item, Data *datas)
{
  AObject	*model;
  Status	*status[2];

  if (!item)
    return;
  status[0] = item->getPrevStatus();
  status[1] = item->getNowStatus();
  if (!status[0] || !status[1])
    return;
  model = item->getModel();
  model->setPos(status[1]->position * CASE_SIZE);
  model->setRot(status[1]->direction);
  if (datas->gameClock)
    model->update(datas->gameClock);
  model->draw();
}

void	Graphic::Graphic::drawScene(Data *datas)
{
  for (std::vector<Primitive::Plan>::iterator ground = this->_ground.begin();
       ground != this->_ground.end();
       ground++)
    (*ground).draw();
  this->_skydome.draw();
  for (std::list<Character::AI *>::const_iterator character = this->_gameInfo.AIs.begin();
       character != this->_gameInfo.AIs.end();
       character++)
    this->updateModel(*character, datas);
  for (std::vector<Character::Player *>::const_iterator character = this->_gameInfo.players.begin();
       character != this->_gameInfo.players.end();
       character++)
    this->updateModel(*character, datas);
  for (int x = 0; x < this->_gameInfo.map->getWidth(); x++)
    for (int y = 0; y < this->_gameInfo.map->getHeight(); y++)
      for (std::list<Map::AEntity *>::const_iterator item = this->_gameInfo.map->at(x, y).getItems().begin();
	   item != this->_gameInfo.map->at(x, y).getItems().end();
	   item++)
	this->updateItem(*item, datas);
}

void	Graphic::Graphic::draw()
{
  Data	*datas = Data::getInstance();
  int	i = 0;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  for (std::vector<Camera>::iterator camera = this->_cameras.begin();
       camera != this->_cameras.end();
       camera++)
    {
      set3DMode();
      (*camera).draw();
      this->drawScene(datas);
      set2DMode(datas);
      this->_gui[i]->draw(this->_gameInfo.players[this->_nbrPlayers - i - 1], this->_gameInfo.map);
      i++;
    }
}

void	Graphic::Graphic::set2DMode(Data *datas) const
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  gluOrtho2D(0, datas->gameSettings.screenWidth,
	     datas->gameSettings.screenHeight, 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glDisable(GL_DEPTH_TEST);
}

void	Graphic::Graphic::set3DMode() const
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  glColor4f(1.f, 1.f, 1.f, 1.f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

Graphic::AObject	*Graphic::Graphic::loadItemModel(Map::e_item itemName, float size)
{
  Data	*data = Data::getInstance();

  for (std::map<Map::e_item, Data::e_model>::iterator item = data->itemsModels.begin();
       item != data->itemsModels.end();
       item++)
    if ((*item).first == itemName)
      return new Model((*item).second);
  for (std::map<Map::e_item, Image>::iterator item = data->itemsTextures.begin();
       item != data->itemsTextures.end();
       item++)
    if ((*item).first == itemName)
      return( new Primitive::Box(CASE_SIZE * size, CASE_SIZE * size,
				 CASE_SIZE * size, &(*item).second));
  return (0);
}
