#include <sstream>
#include "Graphic/GraphicGui.hpp"
#include "Data.hpp"

#define SKILLBAR_WIDTH 377
#define SKILLBAR_HEIGHT 195
#define SKILLSIZE 59
#define LIFEMANABAR_WIDTH 80
#define LIFEMANABAR_HEIGHT 163
#define	AVATAR_SIZE	120
#define	ITEMSIZE	43
#define	BUFFSIZE	30

namespace Graphic
{

  GraphicGui::GraphicGui(const Character::Player *player, float x, float y, int id, int nb_max_gui)
  {
    Data	*datas = Data::getInstance();
    int		textOffsetX = 0;
    int		textOffsetY = 0;

    this->_minimapImgs[0] = std::pair<GraphicGui::ptr_func, Data::e_image>(&Map::GameMap::isWallAt, Data::MINIMAP_WALL);
    this->_minimapImgs[1] = std::pair<GraphicGui::ptr_func, Data::e_image>(&Map::GameMap::isBoxAt, Data::MINIMAP_BOX);
    this->_minimapImgs[2] = std::pair<GraphicGui::ptr_func, Data::e_image>(&Map::GameMap::isExplodingAt, Data::MINIMAP_EXPLOSION);
    this->_minimapImgs[3] = std::pair<GraphicGui::ptr_func, Data::e_image>(&Map::GameMap::isBombAt, Data::RED);
    this->_minimapImgs[4] = std::pair<GraphicGui::ptr_func, Data::e_image>(&Map::GameMap::isBonusAt, Data::YELLOW_CIRCLE);    
    if (nb_max_gui == 2)
      textOffsetY = (id == 1) * 384;
    else if (nb_max_gui == 3)
      {
	textOffsetX = (id == 0) * 683;
	textOffsetY = (id == 2) * 384;
      }
    else if (nb_max_gui == 4)
      {
	textOffsetX = (id == 0 || id == 2) * 683;
	textOffsetY = (id == 2 || id == 3) * 384;
      }
    this->_scale = (nb_max_gui != 1) ? 2.0 : 1.0;
    this->_id = id;
    this->_nb_max_gui = nb_max_gui;
    this->_x = x;
    this->_y = y;
    this->_avatar = new GuiImage(ImagePosition(x + 32 + 302 * (this->_scale == 2),
					       y + 30 + 84 * (this->_scale == 2),
					       x + 32 + AVATAR_SIZE / this->_scale + 302 * (this->_scale == 2),
					       y + 30 + AVATAR_SIZE / this->_scale + 84 * (this->_scale == 2)),
				 player->getChampion()->getAvatarSmall());
    this->_skillBar = new GuiImage(ImagePosition(x + (this->_scale == 2) * 315,
						 y + (this->_scale == 2) * 98,
						 x + SKILLBAR_WIDTH / this->_scale + (this->_scale == 2) * 315,
						 y + SKILLBAR_HEIGHT / this->_scale + (this->_scale == 2) * 98),
				   &datas->imgs[Data::SKILLBAR]);
    this->_life = new GuiImage(ImagePosition(0, 0, 1, 1),
			       &datas->imgs[Data::LIFEBAR]);
    this->_mana = new GuiImage(ImagePosition(0, 0, 1, 1),
			       &datas->imgs[Data::MANABAR]);
    this->_skillImgs[0] = new GuiImage(ImagePosition(this->_x + 312 + 159 * (this->_scale == 2),
						     this->_y + 108 + 44 * (this->_scale == 2),
						     this->_x + 312 + 159 * (this->_scale == 2) + SKILLSIZE / this->_scale,
						     this->_y + 108 + 44 * (this->_scale == 2) + SKILLSIZE / this->_scale),
				       player->getChampion()->getSkillIcon());    
    this->_skillImgs[1] = new GuiImage(ImagePosition(x + 100 + 50 * (this->_scale == 2),
						     y + 20 + 20 * (this->_scale == 2),
						     x + 100 + SKILLSIZE + 50 * (this->_scale == 2),
						     y + 20 + SKILLSIZE + 20 * (this->_scale == 2)),
				       player->getChampion()->getSkillDarkIcon());
    this->_inventory[0] = new GuiImage(ImagePosition(x + 164 + 235 * (this->_scale == 2),
						     y + 126 + 35 * (this->_scale == 2),
						     x + 164 + ITEMSIZE / this->_scale + 235 * (this->_scale == 2),
						     y + 126 + ITEMSIZE / this->_scale + 35 * (this->_scale == 2)),
				       0);
    this->_inventory[1] = new GuiImage(ImagePosition(x + 212 + 210 * (this->_scale == 2),
						     y + 126 + 35 * (this->_scale == 2),
						     x + 212 + ITEMSIZE / this->_scale + 210 * (this->_scale == 2),
						     y + 126 + ITEMSIZE / this->_scale + 35 * (this->_scale == 2)),
				       0);
    this->_inventory[2] = new GuiImage(ImagePosition(x + 260 + 185 * (this->_scale == 2),
						     y + 126 + 35 * (this->_scale == 2),
						     x + 260 + ITEMSIZE / this->_scale + 185 * (this->_scale == 2),
						     y + 126 + ITEMSIZE / this->_scale + 35 * (this->_scale == 2)),
				       0);
    for (int i = 0; i < 3; i++)
      {
	this->_inventoryText[i] = new gdl::Text();
	this->_inventoryText[i]->setSize(20.0 / this->_scale);
      }
    for (int i = 0; i < 6; i++)
      {
	this->_statsText[i] = new gdl::Text();
	this->_statsText[i]->setSize(20.0 / this->_scale);
      }
    this->_skillTimeText = new gdl::Text();
    this->_skillTimeText->setSize(20.0 / this->_scale);
    this->_skillTimeText->setPosition(this->_x + 330 + 150 * (this->_scale == 2) - textOffsetX,
				      this->_y + 125 + 50 * (this->_scale == 2) - textOffsetY);
    for (int i = 0; i < 2; i++)
      {
	this->_pvPmText[i] = new gdl::Text();
	this->_pvPmText[i]->setSize(20.0 / this->_scale);
      }
    this->_pvPmText[0]->setPosition(this->_x + 130 + 230 * (this->_scale == 2) - textOffsetX,
				    this->_y - 15 + 150 * (this->_scale == 2) - textOffsetY);
    this->_pvPmText[1]->setPosition(this->_x + 5 + 320 * (this->_scale == 2) - textOffsetX,
				    this->_y - 15 + 150 * (this->_scale == 2) - textOffsetY);
    this->_statsText[GraphicGui::POWER]->setPosition(this->_x + 200 + BUFFSIZE + 200 * (this->_scale == 2) - textOffsetX,
						     this->_y + 66 - (BUFFSIZE * 2) + 118 * (this->_scale == 2) - textOffsetY);
    this->_statsText[GraphicGui::DEFENSE]->setPosition(this->_x + 290 + BUFFSIZE + 170 * (this->_scale == 2) - textOffsetX,
						       this->_y + 66 - (BUFFSIZE * 2) + 113 * (this->_scale == 2) - textOffsetY);
    this->_statsText[GraphicGui::CRITICAL]->setPosition(this->_x + 200 + BUFFSIZE + 200 * (this->_scale == 2) - textOffsetX,
							this->_y + 68 - BUFFSIZE + 100 * (this->_scale == 2) - textOffsetY);
    this->_statsText[GraphicGui::RESILIENCE]->setPosition(this->_x + 290 + BUFFSIZE + 170 * (this->_scale == 2) - textOffsetX,
							  this->_y + 68 - BUFFSIZE + 100 * (this->_scale == 2) - textOffsetY);
    this->_statsText[GraphicGui::RANGE]->setPosition(this->_x + 200 + BUFFSIZE + 200 * (this->_scale == 2) - textOffsetX,
						     this->_y + 70 + 85 * (this->_scale == 2) - textOffsetY);
    this->_statsText[GraphicGui::SPEED]->setPosition(this->_x + 290 + BUFFSIZE + 170 * (this->_scale == 2) - textOffsetX,
						     this->_y + 70 + 85 * (this->_scale == 2) - textOffsetY);

    this->_statsImgs[GraphicGui::POWER] = new GuiImage(ImagePosition(this->_x + 190.0 + 220.0 * (this->_scale == 2),
								     this->_y + 66.0 - (BUFFSIZE * 2.0) + 50.0 * (this->_scale == 2),
								     this->_x + 190.0 + 220.0 * (this->_scale == 2) + (BUFFSIZE / this->_scale),
								     this->_y + 66.0 - (BUFFSIZE * 2.0) + 50.0 * (this->_scale == 2) + (BUFFSIZE / this->_scale)),
						       &datas->imgs[Data::POWER_POTION]);
    this->_statsImgs[GraphicGui::DEFENSE] = new GuiImage(ImagePosition(this->_x + 280.0 + 190.0 * (this->_scale == 2),
								       this->_y + 66.0 - (BUFFSIZE * 2.0) + 113.0 * (this->_scale == 2),
								       this->_x + 280.0 + 190.0 * (this->_scale == 2) + (BUFFSIZE / this->_scale),
								       this->_y + 66.0 - (BUFFSIZE * 2.0) + 113.0 * (this->_scale == 2) + (BUFFSIZE / this->_scale)),
							 &datas->imgs[Data::DEFENSE_POTION]);
    this->_statsImgs[GraphicGui::CRITICAL] = new GuiImage(ImagePosition(this->_x + 190.0 + 220.0 * (this->_scale == 2),
									this->_y + 68.0 - BUFFSIZE + 100.0 * (this->_scale == 2),
									this->_x + 190.0 + 220.0 * (this->_scale == 2) + (BUFFSIZE / this->_scale),
									this->_y + 68.0 - BUFFSIZE + 100.0 * (this->_scale == 2) + (BUFFSIZE / this->_scale)),
							  &datas->imgs[Data::CRITICAL_POTION]);
    this->_statsImgs[GraphicGui::RESILIENCE] = new GuiImage(ImagePosition(this->_x + 280.0 + 190.0 * (this->_scale == 2),
									  this->_y + 68.0 - BUFFSIZE + 100.0 * (this->_scale == 2),
									  this->_x + 280.0 + 190.0 * (this->_scale == 2) + (BUFFSIZE / this->_scale),
									  this->_y + 68.0 - BUFFSIZE + 100.0 * (this->_scale == 2) + (BUFFSIZE / this->_scale)),
							    &datas->imgs[Data::RESILIENCE_POTION]);
    this->_statsImgs[GraphicGui::RANGE] = new GuiImage(ImagePosition(this->_x + 190.0 + 220.0 * (this->_scale == 2),
								     this->_y + 70.0 + 85.0 * (this->_scale == 2),
								     this->_x + 190.0 + 220.0 * (this->_scale == 2) + (BUFFSIZE / this->_scale),
								     this->_y + 70.0 + 85.0 * (this->_scale == 2) + (BUFFSIZE / this->_scale)),
						       &datas->imgs[Data::RANGE_POTION]);
    this->_statsImgs[GraphicGui::SPEED] = new GuiImage(ImagePosition(this->_x + 280.0 + 190.0 * (this->_scale == 2),
								     this->_y + 70.0 + 85.0 * (this->_scale == 2),
								     this->_x + 280.0 + 190.0 * (this->_scale == 2) + BUFFSIZE / this->_scale,
								     this->_y + 70.0 + 85.0 * (this->_scale == 2) + BUFFSIZE / this->_scale),
						       &datas->imgs[Data::SPEED_POTION]);
  }

  GraphicGui::~GraphicGui()
  {
    if (this->_skillBar)
      delete this->_skillBar;
    if (this->_life)
      delete this->_life;
    if (this->_mana)
      delete this->_mana;
  }

  void	GraphicGui::setPosition(float x, float y)
  {
    if (this->_skillBar)
      this->_skillBar->setImagePosition(ImagePosition(x, y, x + SKILLBAR_WIDTH, y + SKILLBAR_HEIGHT));
  }

  void	GraphicGui::createSquare(float x, float y, double width, double height)
  {
    glBegin(GL_QUADS);
    glColor3d(0xFF, 0xFF, 0xFF);
    glTexCoord2f(0.0,0.0);
    glVertex2f(x, y + height);
    glTexCoord2f(1.0,0.0);
    glVertex2f(x + width, y + height);
    glTexCoord2f(1.0,1.0);
    glVertex2f(x + width, y);
    glTexCoord2f(0.0,1.0);
    glVertex2f(x, y);
    glEnd();
  }

  void	GraphicGui::drawMiniMap(Map::GameMap *map, const Character::Player *player)
  {
    float	case_size = 225.0 / ((map->getWidth() > map->getHeight()) ? map->getWidth() : map->getHeight());
    Data	*datas = Data::getInstance();

    case_size /= this->_scale;
    glDisable(GL_BLEND); 
    for (int x = 0; x < map->getWidth(); x++)
      for (int y = 0; y < map->getHeight(); y++)
	{
	  datas->imgs[Data::MINIMAP_BG].bind();
	  if (map->isPlayerAt(x, y, player) > 0)
	    {
	      if (map->isPlayerAt(x, y, player) == 1)
		datas->imgs[Data::RED_CIRCLE].bind();
	      else if (map->isPlayerAt(x, y, player) == 2)
		datas->imgs[Data::GREEN_CIRCLE].bind();
	      else
		datas->imgs[Data::GREY_CIRCLE].bind();
	    }
	  else
	    {
	      for (std::map<int, std::pair<GraphicGui::ptr_func, Data::e_image> >::iterator i = this->_minimapImgs.begin();
		   i != this->_minimapImgs.end();
		   i++)
		if ( (map->*i->second.first)(x, y))
		  datas->imgs[i->second.second].bind();
	    }
	  createSquare(this->_x + SKILLBAR_WIDTH + 10.0 + x * case_size + (this->_scale == 2) * 122,
		       this->_y - 40.0 + y * case_size + (this->_scale == 2) * 117,
		       case_size, case_size);
	}
  }

  void	GraphicGui::draw(const Character::Player *player, Map::GameMap *map)
  {
    const Statistics &stats = player->getAllStats();
    Data	*datas = Data::getInstance();    
    this->_skillBar->draw();
    this->_avatar->draw();
    for (int i = 0; i < 3; i++)
      {
	this->_inventory[i]->setImage((player->getInventory()[i] == 0) ? 0 : player->getInventory()[i]->getIcon());
	this->_inventory[i]->draw();
      }
    this->_life->setImagePosition(ImagePosition(this->_x + 96 + (this->_scale == 2) * 267,
						this->_y + 10 + (this->_scale == 2) * 94,
						this->_x + 96 + LIFEMANABAR_WIDTH / this->_scale + (this->_scale == 2) * 267,
						this->_y + 10 + LIFEMANABAR_HEIGHT / this->_scale + (this->_scale == 2) * 94));
    this->_life->draw(stats.get(Statistics::HP) * 100.0 / stats.get(Statistics::HP_MAX));
    this->_mana->setImagePosition(ImagePosition(this->_x + 10 + (this->_scale == 2) * 312,
						this->_y + 10 + (this->_scale == 2) * 94,
						this->_x + 10 + LIFEMANABAR_WIDTH / this->_scale + (this->_scale == 2) * 312,
						this->_y + 10 + LIFEMANABAR_HEIGHT / this->_scale + (this->_scale == 2)* 94));
    this->_mana->draw(stats.get(Statistics::MANA) * 100.0 / stats.get(Statistics::MANA_MAX));
    
    this->_skillImgs[0]->draw();
    this->_skillImgs[1]->setImagePosition(ImagePosition(this->_x + 312 + 159 * (this->_scale == 2),
							this->_y + 108 + 44 * (this->_scale == 2),
							this->_x + 312 + 159 * (this->_scale == 2) + SKILLSIZE / this->_scale,
							this->_y + 108 + 44 * (this->_scale == 2) + SKILLSIZE / this->_scale));
    if (player->getChampion()->getSkillTimePercent() > 0)
      this->_skillImgs[1]->draw(player->getChampion()->getSkillTimePercent());
    if (datas->gameSettings.minimap)
      drawMiniMap(map, player);

    if (this->_nb_max_gui > 2)
      return;

    std::ostringstream buff;
    buff << stats.get(Statistics::POWER);
    this->_statsText[GraphicGui::POWER]->setText(buff.str());
    buff.str("");
    buff << stats.get(Statistics::SPEED);
    this->_statsText[GraphicGui::SPEED]->setText(buff.str());
    buff.str("");
    buff << stats.get(Statistics::RESILIENCE);
    this->_statsText[GraphicGui::RESILIENCE]->setText(buff.str());
    buff.str("");
    buff << stats.get(Statistics::DEFENSE);
    this->_statsText[GraphicGui::DEFENSE]->setText(buff.str());
    buff.str("");
    buff << stats.get(Statistics::CRITICAL);
    this->_statsText[GraphicGui::CRITICAL]->setText(buff.str());
    buff.str("");
    buff << stats.get(Statistics::RANGE);
    this->_statsText[GraphicGui::RANGE]->setText(buff.str());
    buff.str("");
    buff << stats.get(Statistics::HP) << "/" << stats.get(Statistics::HP_MAX);
    this->_pvPmText[0]->setText(buff.str());
    buff.str("");
    buff << stats.get(Statistics::MANA) << "/" << stats.get(Statistics::MANA_MAX);
    this->_pvPmText[1]->setText(buff.str());
    buff.str("");
    float percent = player->getChampion()->getSkillTimeRemain();
    if (percent > 10)
      buff << static_cast<int>(player->getChampion()->getSkillTimeRemain());
    else if (percent > 0)
      buff << (static_cast<int>(player->getChampion()->getSkillTimeRemain() * 10) / 10.0);
    this->_skillTimeText->setText(buff.str());

    for (int i = 0; i < 3; i++)
      {
	buff.str("");
	if (player->getInventory()[i] && player->getInventory()[i]->getQuantity() > 1)
	  buff << player->getInventory()[i]->getQuantity();
	this->_inventoryText[i]->setText(buff.str());
	this->_inventoryText[i]->setPosition(this->_x + 165 + 48 * i, this->_y + 145);
      }

    this->_statsImgs[GraphicGui::POWER]->setImagePosition(ImagePosition(this->_x + 190.0 + 220.0 * (this->_scale == 2),
									this->_y + 66.0 - (BUFFSIZE * 2.0) + 50.0 * (this->_scale == 2),
									this->_x + 190.0 + 220.0 * (this->_scale == 2) + (BUFFSIZE / this->_scale),
									this->_y + 66.0 - (BUFFSIZE * 2.0) + 50.0 * (this->_scale == 2) + (BUFFSIZE / this->_scale)));
    this->_statsImgs[GraphicGui::DEFENSE]->setImagePosition(ImagePosition(this->_x + 280.0 + 190.0 * (this->_scale == 2),
									  this->_y + 66.0 - (BUFFSIZE * 2.0) + 50.0 * (this->_scale == 2),
									  this->_x + 280.0 + 190.0 * (this->_scale == 2) + (BUFFSIZE / this->_scale),
									  this->_y + 66.0 - (BUFFSIZE * 2.0) + 50.0 * (this->_scale == 2) + (BUFFSIZE / this->_scale)));
    this->_statsImgs[GraphicGui::CRITICAL]->setImagePosition(ImagePosition(this->_x + 190.0 + 220.0 * (this->_scale == 2),
									   this->_y + 68.0 - BUFFSIZE + 50.0 * (this->_scale == 2),
									   this->_x + 190.0 + 220.0 * (this->_scale == 2) + (BUFFSIZE / this->_scale),
									   this->_y + 68.0 - BUFFSIZE + 50.0 * (this->_scale == 2) + (BUFFSIZE / this->_scale)));
    this->_statsImgs[GraphicGui::RESILIENCE]->setImagePosition(ImagePosition(this->_x + 280.0 + 190.0 * (this->_scale == 2),
									     this->_y + 68.0 - BUFFSIZE + 50.0 * (this->_scale == 2),
									     this->_x + 280.0 + 190.0 * (this->_scale == 2) + (BUFFSIZE / this->_scale),
									     this->_y + 68.0 - BUFFSIZE + 50.0 * (this->_scale == 2) + (BUFFSIZE / this->_scale)));
    this->_statsImgs[GraphicGui::RANGE]->setImagePosition(ImagePosition(this->_x + 190.0 + 220.0 * (this->_scale == 2),
									this->_y + 70.0 + 50.0 * (this->_scale == 2),
									this->_x + 190.0 + 220.0 * (this->_scale == 2) + (BUFFSIZE / this->_scale),
									this->_y + 70.0 + 50.0 * (this->_scale == 2) + (BUFFSIZE / this->_scale)));
    this->_statsImgs[GraphicGui::SPEED]->setImagePosition(ImagePosition(this->_x + 280.0 + 190.0 * (this->_scale == 2),
									this->_y + 70.0 + 50.0 * (this->_scale == 2),
									this->_x + 280.0 + 190.0 * (this->_scale == 2) + BUFFSIZE / this->_scale,
									this->_y + 70.0 + 50.0 * (this->_scale == 2) + BUFFSIZE / this->_scale));
    for (int i = 0; i < 6; i++)
      this->_statsImgs[i]->draw();
    for (int i = 0; i < 6; i++)
      {
	this->_statsText[i]->draw();
	if (i < 2)
	  this->_pvPmText[i]->draw();
	if (i < 3)
	  this->_inventoryText[i]->draw();
      }
    this->_skillTimeText->draw();
  }

};
