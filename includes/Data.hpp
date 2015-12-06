#ifndef __DATA__
#define __DATA__

# include <map>
# include <list>

# include "GameSettings.hpp"
# include "GDL/Image.hpp"
# include "GDL/Model.hpp"
# include "GDL/GameClock.hpp"
# include "Database/Database.hpp"
# include "State/StateManager.hpp"
# include "Graphic/GuiImage.hpp"
# include "Sound/ISoundManager.hpp"

#define AVATAR "ressources/images/avatars/"
#define MENU "ressources/images/menu/"

namespace Champion
{
  class Champion;
};

class Data
{
private :
  Data();
  ~Data();

public :
  enum e_image
    {
      CORKI_SMALL_AVATAR,
      CORKI_FULL_AVATAR,
      CORKI_SKILL_ICON,
      CORKI_SKILL_DARK_ICON,
      CHOGATH_SMALL_AVATAR,
      CHOGATH_FULL_AVATAR,
      CHOGATH_SKILL_ICON,
      CHOGATH_SKILL_DARK_ICON,
      RYZE_SMALL_AVATAR,
      RYZE_FULL_AVATAR,
      RYZE_SKILL_ICON,
      RYZE_SKILL_DARK_ICON,
      NOCTURNE_SMALL_AVATAR,
      NOCTURNE_FULL_AVATAR,
      NOCTURNE_SKILL_ICON,
      NOCTURNE_SKILL_DARK_ICON,
      FIDDLESTICK_SMALL_AVATAR,
      FIDDLESTICK_FULL_AVATAR,
      FIDDLESTICK_SKILL_ICON,
      FIDDLESTICK_SKILL_DARK_ICON,
      MINION_SMALL_AVATAR,
      MEDAL_BRONZE,
      MEDAL_SILVER,
      MEDAL_GOLD,
      MEDAL_PLATINE,
      MEDAL_DIAMOND,
      MEDAL_CHALLENGER,
      BARRE,
      BG_BUTTON,
      BG_BUTTON_OVER,
      BG_BUTTON_CLICKED,
      BG_MENU,
      LAYOUT_PAUSE,
      LAYOUT_OPTION,
      PREV_ARROW,
      PREV_ARROW_OVER,
      PREV_ARROW_CLICKED,
      NEXT_ARROW,
      NEXT_ARROW_OVER,
      NEXT_ARROW_CLICKED,
      BG_KEYS,
      BG_KEYS_OVER,
      BG_KEYS_CLICKED,
      ALL_SKILL_ICONS,
      SKILL_ICON,
      SELECT_PLAYER_SHADOW,
      SELECT_PLAYER_SHADOW_TEXT,
      HP_BAR,
      MANA_BAR,
      CRIT_BAR,
      POWER_BAR,
      DEF_BAR,
      RESI_BAR,
      RANGE_BAR,
      SPEED_BAR,
      PROFILE_NAME_BACK,
      CHECKBOX_CHECKED,
      CHECKBOX_UNCHECKED,
      BINDINGS_BACK,
      BINDINGS_KEY_BACK,
      CURSOR,
      SKYDOME,
      GROUND,
      SKILLBAR,
      LIFEBAR,
      MANABAR,
      CLASSIC_WALL,
      CLASSIC_BOX,
      IRON_BOX,
      ULTIMA_BOX,
      CLASSIC_EXPLOSION,
      LIFE_POTION,
      LIFE_MAX_POTION,
      MANA_POTION,
      MANA_MAX_POTION,
      CRITICAL_POTION,
      DEFENSE_POTION,
      POWER_POTION,
      RANGE_POTION,
      RESILIENCE_POTION,
      SPEED_POTION,
      RED,
      BLUE,
      YELLOW,
      ORANGE,
      BLACK,
      GREEN,
      PURPLE,
      RED_CIRCLE,
      GREEN_CIRCLE,
      YELLOW_CIRCLE,
      GREY_CIRCLE,
      MINIMAP_BG,
      MINIMAP_BOX,
      MINIMAP_WALL,
      MINIMAP_EXPLOSION,
      MISSILE_RESSOURCE_ICON,
      REBON_RESSOURCE_ICON,
      FUFU_RESSOURCE_ICON,
      X_RESSOURCE_ICON,
      MINE_RESSOURCE_ICON,
      BRAIN_RESSOURCE_ICON,
      PIERCING_RESSOURCE_ICON,
      INTRO_1,
      INTRO_2,
      INTRO_3,
      CREDITS
    };

  enum	e_model
    {
      MINION_MODEL,
      CORKI_MODEL,
      CHOGATH_MODEL,
      RYZE_MODEL,
      NOCTURNE_MODEL,
      FIDDLESTICK_MODEL,
      WALL_MODEL,
      CLASSIC_BOMB_MODEL,
      MISSILE_BOMB_MODEL,
      REBON_BOMB_MODEL,
      X_BOMB_MODEL,
      PERFO_BOMB_MODEL,
      EXPLOSION_MODEL
    };

  Database::Database			db;
  bool					IsGameRunning;
  GameSettings				gameSettings;
  Sound::ISoundManager			*soundManager;
  State::StateManager			*states;
  gdl::GameClock			*gameClock;
  std::map<e_image, Graphic::Image >	imgs;
  std::list<Champion::Champion *>	championsPool;
  std::map<Map::e_item, e_model>	itemsModels;
  std::map<Map::e_item, Graphic::Image>	itemsTextures;
  std::map<e_model, std::string>	modelsName;


  // Retourne l'instance de l'objet data si elle existe sinon la cree.
  static Data		*getInstance();

  // Delete l'instance de l'objet data si il existe.
  static void		kill();

  void	loadModels();

private:
  static Data *obj_;
};

#endif
