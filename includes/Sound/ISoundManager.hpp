#ifndef __ISOUNDMANAGER_HPP__
#define __ISOUNDMANAGER_HPP__

namespace Sound
{
  enum e_sound
    {
      CLASSIC_BOMB_NOISE,
      MENU_MUSIC,
      ARCADE_MUSIC,
      REBON_BOMB_NOISE,
      FUFU_CORKI_BOMB_NOISE,
      FUFU_CHOGATH_BOMB_NOISE,
      FUFU_NOCTURNE_BOMB_NOISE,
      FUFU_RYZE_BOMB_NOISE,
      FUFU_FIDDLESTICK_BOMB_NOISE,
      MISSILE_BOMB_NOISE,
      CHOGATH_SKILL_VOICE,
      FIDDLE_SKILL_VOICE,
      RYZE_SKILL_VOICE,
      NOCTURNE_SKILL_VOICE,
      CORKI_SKILL_VOICE,
      CORKI_DMG_VOICE,
      CHOGATH_DMG_VOICE,
      FIDDLE_DMG_VOICE,
      RYZE_DMG_VOICE,
      NOCTURNE_DMG_VOICE
    };

  enum e_soundType
    {
      AMBIANCE,
      NOISE,
      VOICE
    };

  class ISoundManager
  {
  public:
    ISoundManager() {};
    virtual ~ISoundManager() {};

    virtual void	playSound(e_sound) = 0;
    virtual void	changeVol(Sound::e_soundType type, int vol) = 0;
    virtual void	stopSound(Sound::e_sound) = 0;
  };
};

#endif
