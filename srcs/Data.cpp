#include "Data.hpp"
#include "Sound/FmodManager.hpp"

Data::Data()
{

  this->imgs[Data::CORKI_SMALL_AVATAR] = Graphic::Image(std::string(AVATAR) + std::string("corki/corkiSmall.png"));
  this->imgs[Data::CORKI_FULL_AVATAR] = Graphic::Image(std::string(AVATAR) + std::string("corki/corkiFull.png"));
  this->imgs[Data::CORKI_SKILL_ICON] = Graphic::Image(std::string(AVATAR) + std::string("corki/corkiSkill.png"));
  this->imgs[Data::CORKI_SKILL_DARK_ICON] = Graphic::Image(std::string(AVATAR) + std::string("corki/corkiDarkSkill.png"));
  this->imgs[Data::RYZE_SMALL_AVATAR] = Graphic::Image(std::string(AVATAR) + std::string("ryze/ryzeSmall.png"));
  this->imgs[Data::RYZE_FULL_AVATAR] = Graphic::Image(std::string(AVATAR) + std::string("ryze/ryzeFull.png"));
  this->imgs[Data::RYZE_SKILL_ICON] = Graphic::Image(std::string(AVATAR) + std::string("ryze/ryzeSkill.png"));
  this->imgs[Data::RYZE_SKILL_DARK_ICON] = Graphic::Image(std::string(AVATAR) + std::string("ryze/ryzeDarkSkill.png"));
  this->imgs[Data::CHOGATH_SMALL_AVATAR] = Graphic::Image(std::string(AVATAR) + std::string("chogath/chogathSmall.png"));
  this->imgs[Data::CHOGATH_FULL_AVATAR] = Graphic::Image(std::string(AVATAR) + std::string("chogath/chogathFull.png"));
  this->imgs[Data::CHOGATH_SKILL_ICON] = Graphic::Image(std::string(AVATAR) + std::string("chogath/chogathSkill.png"));
  this->imgs[Data::CHOGATH_SKILL_DARK_ICON] = Graphic::Image(std::string(AVATAR) + std::string("chogath/chogathDarkSkill.png"));
  this->imgs[Data::NOCTURNE_SMALL_AVATAR] = Graphic::Image(std::string(AVATAR) + std::string("nocturne/nocturneSmall.png"));
  this->imgs[Data::NOCTURNE_FULL_AVATAR] = Graphic::Image(std::string(AVATAR) + std::string("nocturne/nocturneFull.png"));
  this->imgs[Data::NOCTURNE_SKILL_ICON] = Graphic::Image(std::string(AVATAR) + std::string("nocturne/nocturneSkill.png"));
  this->imgs[Data::NOCTURNE_SKILL_DARK_ICON] = Graphic::Image(std::string(AVATAR) + std::string("nocturne/nocturneDarkSkill.png"));
  this->imgs[Data::FIDDLESTICK_SMALL_AVATAR] = Graphic::Image(std::string(AVATAR) + std::string("fiddlestick/fiddlestickSmall.png"));
  this->imgs[Data::FIDDLESTICK_FULL_AVATAR] = Graphic::Image(std::string(AVATAR) + std::string("fiddlestick/fiddlestickFull.png"));
  this->imgs[Data::FIDDLESTICK_SKILL_ICON] = Graphic::Image(std::string(AVATAR) + std::string("fiddlestick/fiddlestickSkill.png"));
  this->imgs[Data::FIDDLESTICK_SKILL_DARK_ICON] = Graphic::Image(std::string(AVATAR) + std::string("fiddlestick/fiddlestickDarkSkill.png"));
  this->imgs[Data::MINION_SMALL_AVATAR] = Graphic::Image(std::string(AVATAR) + std::string("minion/minionSmall.png"));
  this->imgs[Data::LAYOUT_PAUSE] = Graphic::Image(std::string(MENU) + std::string("LayoutPause.png"));
  this->imgs[Data::BARRE] = Graphic::Image(std::string(MENU) + std::string("Barre.png"));
  this->imgs[Data::BG_BUTTON] = Graphic::Image(std::string(MENU) + std::string("boutonNormal.png"));
  this->imgs[Data::BG_BUTTON_OVER] = Graphic::Image(std::string(MENU) + std::string("boutonOver.png"));
  this->imgs[Data::BG_BUTTON_CLICKED] = Graphic::Image(std::string(MENU) + std::string("boutonClicked.png"));
  this->imgs[Data::BG_KEYS] =  Graphic::Image(std::string(MENU) + std::string("binding/BindKeyBackground.png"));
  this->imgs[Data::BG_KEYS_OVER] = Graphic::Image(std::string(MENU) + std::string("binding/editBoxControlSettingsOver.png"));
  this->imgs[Data::BG_KEYS_CLICKED] = Graphic::Image(std::string(MENU) + std::string("binding/editBoxControlSettingsClicked.png"));
  this->imgs[Data::BG_MENU] = Graphic::Image(std::string(MENU) + std::string("bg_menu.jpg"));
  this->imgs[Data::CHECKBOX_CHECKED] = Graphic::Image(std::string(MENU) + std::string("checkBoxCheck.png"));
  this->imgs[Data::CHECKBOX_UNCHECKED] = Graphic::Image(std::string(MENU) + std::string("checkBoxUncheck.png"));
  this->imgs[Data::CURSOR] = Graphic::Image(std::string(MENU) + std::string("Cursor.png"));
  this->imgs[Data::PREV_ARROW] = Graphic::Image(std::string(MENU) + std::string("PrevArrow.png"));
  this->imgs[Data::PREV_ARROW_OVER] = Graphic::Image(std::string(MENU) + std::string("PrevArrowOver.png"));
  this->imgs[Data::PREV_ARROW_CLICKED] = Graphic::Image(std::string(MENU) + std::string("PrevArrowClicked.png"));
  this->imgs[Data::NEXT_ARROW] = Graphic::Image(std::string(MENU) + std::string("NextArrow.png"));
  this->imgs[Data::NEXT_ARROW_OVER] = Graphic::Image(std::string(MENU) + std::string("NextArrowOver.png"));
  this->imgs[Data::NEXT_ARROW_CLICKED] = Graphic::Image(std::string(MENU) + std::string("NextArrowClicked.png"));
  this->imgs[Data::ALL_SKILL_ICONS] = Graphic::Image(std::string(MENU) + std::string("AllSkillIcons.png"));
  this->imgs[Data::SKILL_ICON] = Graphic::Image(std::string(MENU) + std::string("skillIcon.png"));
  this->imgs[Data::SELECT_PLAYER_SHADOW] = Graphic::Image(std::string(MENU) + std::string("SelectPlayerShadow.png"));
  this->imgs[Data::SELECT_PLAYER_SHADOW_TEXT] = Graphic::Image(std::string(MENU) + std::string("SelectPlayerShadowText.png"));
  this->imgs[Data::HP_BAR] = Graphic::Image(std::string(MENU) + std::string("HpBar.png"));
  this->imgs[Data::MANA_BAR] = Graphic::Image(std::string(MENU) + std::string("ManaBar.png"));
  this->imgs[Data::POWER_BAR] = Graphic::Image(std::string(MENU) + std::string("PowerBar.png"));
  this->imgs[Data::DEF_BAR] = Graphic::Image(std::string(MENU) + std::string("DefBar.png"));
  this->imgs[Data::CRIT_BAR] = Graphic::Image(std::string(MENU) + std::string("CritBar.png"));
  this->imgs[Data::RESI_BAR] = Graphic::Image(std::string(MENU) + std::string("ResiBar.png"));
  this->imgs[Data::RANGE_BAR] = Graphic::Image(std::string(MENU) + std::string("RangeBar.png"));
  this->imgs[Data::SPEED_BAR] = Graphic::Image(std::string(MENU) + std::string("SpeedBar.png"));
  this->imgs[Data::LAYOUT_OPTION] = Graphic::Image(std::string(MENU) + std::string("LayoutSetting.png"));
  this->imgs[Data::PROFILE_NAME_BACK] = Graphic::Image("ressources/images/menu/ProfilNameBackground.png");
  this->imgs[Data::LAYOUT_OPTION] = Graphic::Image(std::string(MENU) + std::string("LayoutSetting.png"));
  this->imgs[Data::BINDINGS_BACK] =  Graphic::Image("ressources/images/menu/binding/BindBackground.png");
  this->imgs[Data::BINDINGS_KEY_BACK] =  Graphic::Image("ressources/images/menu/binding/BindKeyBackground.png");
  this->imgs[Data::SKYDOME] = Graphic::Image("ressources/images/graphic/skydome.jpg");
  this->imgs[Data::GROUND] = Graphic::Image("ressources/images/graphic/ground.png");
  this->imgs[Data::SKILLBAR] = Graphic::Image("ressources/images/graphic/skillbar.png");
  this->imgs[Data::LIFEBAR] = Graphic::Image("ressources/images/graphic/life.png");
  this->imgs[Data::MANABAR] = Graphic::Image("ressources/images/graphic/mana.png");
  this->imgs[Data::CLASSIC_WALL] = Graphic::Image("ressources/images/caisses/eb_crate_variant001.tga");
  this->imgs[Data::CLASSIC_EXPLOSION] = Graphic::Image("ressources/images/colors/orange.png");
  this->imgs[Data::CLASSIC_BOX] = Graphic::Image("ressources/images/caisses/eb_crate_variant002.tga");
  this->imgs[Data::IRON_BOX] = Graphic::Image("ressources/images/caisses/eb_crate_variant003.tga");
  this->imgs[Data::ULTIMA_BOX] = Graphic::Image("ressources/images/caisses/eb_crate_variant004.tga");

  this->imgs[Data::MEDAL_BRONZE] = Graphic::Image("ressources/images/menu/bronzeMedal.png");
  this->imgs[Data::MEDAL_SILVER] = Graphic::Image("ressources/images/menu/silverMedal.png");
  this->imgs[Data::MEDAL_GOLD] = Graphic::Image("ressources/images/menu/goldMedal.png");
  this->imgs[Data::MEDAL_PLATINE] = Graphic::Image("ressources/images/menu/platineMedal.png");
  this->imgs[Data::MEDAL_DIAMOND] = Graphic::Image("ressources/images/menu/diamondMedal.png");
  this->imgs[Data::MEDAL_CHALLENGER] = Graphic::Image("ressources/images/menu/chalengerMedal.png");

  this->imgs[Data::RED] = Graphic::Image("ressources/images/colors/red.png");
  this->imgs[Data::BLUE] = Graphic::Image("ressources/images/colors/blue.png");
  this->imgs[Data::YELLOW] = Graphic::Image("ressources/images/colors/yellow.png");
  this->imgs[Data::ORANGE] = Graphic::Image("ressources/images/colors/orange.png");
  this->imgs[Data::BLACK] = Graphic::Image("ressources/images/colors/black.png");
  this->imgs[Data::GREEN] = Graphic::Image("ressources/images/colors/green.png");
  this->imgs[Data::PURPLE] = Graphic::Image("ressources/images/colors/purple.png");

  this->imgs[Data::LIFE_MAX_POTION] = Graphic::Image("ressources/images/buff/hpmax.png");
  this->imgs[Data::LIFE_POTION] = Graphic::Image("ressources/images/buff/hp.png");
  this->imgs[Data::MANA_MAX_POTION] = Graphic::Image("ressources/images/buff/manamax.png");
  this->imgs[Data::MANA_POTION] = Graphic::Image("ressources/images/buff/mana.png");
  this->imgs[Data::CRITICAL_POTION] = Graphic::Image("ressources/images/buff/critical.png");
  this->imgs[Data::DEFENSE_POTION] = Graphic::Image("ressources/images/buff/defense.png");
  this->imgs[Data::POWER_POTION] = Graphic::Image("ressources/images/buff/power.png");
  this->imgs[Data::RANGE_POTION] = Graphic::Image("ressources/images/buff/range.png");
  this->imgs[Data::RESILIENCE_POTION] = Graphic::Image("ressources/images/buff/resilience.png");
  this->imgs[Data::SPEED_POTION] = Graphic::Image("ressources/images/buff/speed.png");

  this->imgs[Data::RED_CIRCLE] = Graphic::Image("ressources/images/minimap/red_circle.png");
  this->imgs[Data::GREEN_CIRCLE] = Graphic::Image("ressources/images/minimap/green_circle.png");
  this->imgs[Data::YELLOW_CIRCLE] = Graphic::Image("ressources/images/minimap/yellow_circle.png");
  this->imgs[Data::GREY_CIRCLE] = Graphic::Image("ressources/images/minimap/grey_circle.png");
  this->imgs[Data::MINIMAP_BG] = Graphic::Image("ressources/images/minimap/background.png");
  this->imgs[Data::MINIMAP_BOX] = Graphic::Image("ressources/images/minimap/box.png");
  this->imgs[Data::MINIMAP_WALL] = Graphic::Image("ressources/images/minimap/wall.png");
  this->imgs[Data::MINIMAP_EXPLOSION] = Graphic::Image("ressources/images/minimap/explosion.png");

  this->imgs[Data::MISSILE_RESSOURCE_ICON] = Graphic::Image("ressources/images/inventory/MissilebombIcone.png");
  this->imgs[Data::REBON_RESSOURCE_ICON] = Graphic::Image("ressources/images/inventory/bombRebondIcone.png");
  this->imgs[Data::X_RESSOURCE_ICON] = Graphic::Image("ressources/images/inventory/XbombIcone.png");
  this->imgs[Data::FUFU_RESSOURCE_ICON] = Graphic::Image("ressources/images/inventory/FufubombIcone.png");
  this->imgs[Data::BRAIN_RESSOURCE_ICON] = Graphic::Image("ressources/images/inventory/brainRessourceIcone.png");
  this->imgs[Data::PIERCING_RESSOURCE_ICON] = Graphic::Image("ressources/images/inventory/PerfoBombMissile.png");
  this->imgs[Data::MINE_RESSOURCE_ICON] = Graphic::Image("ressources/images/inventory/MinebombIcone.png");
  this->imgs[Data::INTRO_1] = Graphic::Image("ressources/images/menu/Intro_credit/intro1.png");
  this->imgs[Data::INTRO_2] = Graphic::Image("ressources/images/menu/Intro_credit/intro2.png");
  this->imgs[Data::INTRO_3] = Graphic::Image("ressources/images/menu/Intro_credit/intro3.png");
  this->imgs[Data::CREDITS] = Graphic::Image("ressources/images/menu/Intro_credit/creditBG.png");

  this->itemsModels[Map::CLASSIC_BOMB] = Data::CLASSIC_BOMB_MODEL;
  this->itemsModels[Map::CLASSIC_EXPLOSION] = Data::EXPLOSION_MODEL;
  this->itemsModels[Map::MISSILE_BOMB] = Data::MISSILE_BOMB_MODEL;
  this->itemsModels[Map::X_BOMB] = Data::X_BOMB_MODEL;
  this->itemsModels[Map::PERFO_BOMB] = Data::PERFO_BOMB_MODEL;
  this->itemsModels[Map::REBON_BOMB] = Data::REBON_BOMB_MODEL;
  this->itemsModels[Map::PIERCING_BOMB] = Data::PERFO_BOMB_MODEL;

  this->itemsTextures[Map::CLASSIC_WALL] = this->imgs[Data::CLASSIC_WALL];

  this->itemsTextures[Map::CLASSIC_BOX] = this->imgs[Data::CLASSIC_BOX];
  this->itemsTextures[Map::IRON_BOX] = this->imgs[Data::IRON_BOX];
  this->itemsTextures[Map::ULTIMA_BOX] = this->imgs[Data::ULTIMA_BOX];

  this->itemsTextures[Map::LIFE_POTION] = this->imgs[Data::LIFE_POTION];
  this->itemsTextures[Map::BUFF_LIFE_MAX] = this->imgs[Data::LIFE_MAX_POTION];
  this->itemsTextures[Map::MANA_POTION] = this->imgs[Data::MANA_POTION];
  this->itemsTextures[Map::BUFF_MANA_MAX] = this->imgs[Data::MANA_MAX_POTION];
  this->itemsTextures[Map::BUFF_CRITICAL] = this->imgs[Data::CRITICAL_POTION];
  this->itemsTextures[Map::BUFF_DEFENSE] = this->imgs[Data::DEFENSE_POTION];
  this->itemsTextures[Map::BUFF_POWER] = this->imgs[Data::POWER_POTION];
  this->itemsTextures[Map::BUFF_RANGE] = this->imgs[Data::RANGE_POTION];
  this->itemsTextures[Map::BUFF_RESILIENCE] = this->imgs[Data::RESILIENCE_POTION];
  this->itemsTextures[Map::BUFF_SPEED] = this->imgs[Data::SPEED_POTION];
  this->itemsTextures[Map::MISSILE_RESSOURCE] = this->imgs[Data::MISSILE_RESSOURCE_ICON];
  this->itemsTextures[Map::REBON_RESSOURCE] = this->imgs[Data::REBON_RESSOURCE_ICON];
  this->itemsTextures[Map::X_RESSOURCE] = this->imgs[Data::X_RESSOURCE_ICON];
  this->itemsTextures[Map::PIERCING_RESSOURCE] = this->imgs[Data::PIERCING_RESSOURCE_ICON];
  this->itemsTextures[Map::MINE_RESSOURCE] = this->imgs[Data::MINE_RESSOURCE_ICON];
  this->itemsTextures[Map::FUFU_RESSOURCE] = this->imgs[Data::FUFU_RESSOURCE_ICON];
  this->itemsTextures[Map::BRAIN_RESSOURCE] = this->imgs[Data::BRAIN_RESSOURCE_ICON];

  this->modelsName[Data::CORKI_MODEL] = "corki";
  this->modelsName[Data::MINION_MODEL] = "ai";
  this->modelsName[Data::CHOGATH_MODEL] = "chogath";
  this->modelsName[Data::RYZE_MODEL] = "ryze";
  this->modelsName[Data::NOCTURNE_MODEL] = "nocturne";
  this->modelsName[Data::FIDDLESTICK_MODEL] = "fiddlestick";
  this->modelsName[Data::CLASSIC_BOMB_MODEL] = "bomb";
  this->modelsName[Data::MISSILE_BOMB_MODEL] = "missileBomb";
  this->modelsName[Data::X_BOMB_MODEL] = "xBomb";
  this->modelsName[Data::REBON_BOMB_MODEL] = "rebonBomb";
  this->modelsName[Data::PERFO_BOMB_MODEL] = "perfoBomb";
  this->modelsName[Data::EXPLOSION_MODEL] = "explosion";

  this->soundManager = new Fmod::FmodManager(this->db.getMusicVol(), this->db.getNoisesVol(),
					     this->db.getVoicesVol());
  this->gameSettings.init(this->db.getMinimap(), this->db.getLanguage());
}

Data::~Data()
{
}

Data	*Data::getInstance()
{
  if (!obj_)
    {
      obj_ = new Data();
      return (obj_);
    }
  else
    return (obj_);
}

void	Data::kill()
{
  if (obj_)
    delete (obj_);
  obj_ = 0;
}

Data	*Data::obj_ = 0;
