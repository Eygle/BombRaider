#include <iostream>

#include "Sound/FmodManager.hpp"
#include "Sound/FmodSound.hpp"

Fmod::FmodManager::FmodManager(int music, int noise, int voice)
{
  FMODError(FMOD::System_Create(&this->sys_));
  FMODError(this->sys_->init(50 ,FMOD_INIT_NORMAL, 0));
  this->listSound_[Sound::MENU_MUSIC] = new Fmod::FmodSound(this->sys_,
							    "./ressources/sounds/LaCompileDeLete.mp3",
							    Sound::MENU_MUSIC , Sound::AMBIANCE,
							    false, this->channel1_);
  this->listSound_[Sound::ARCADE_MUSIC] = new Fmod::FmodSound(this->sys_,
							      "./ressources/sounds/LaCompileDesPompiers2.mp3",
							      Sound::ARCADE_MUSIC , Sound::AMBIANCE,
							      false, this->channel2_);
  this->listSound_[Sound::CLASSIC_BOMB_NOISE] = new Fmod::FmodSound(this->sys_,
								    "./ressources/sounds/soundexplosion2.mp3",
								    Sound::CLASSIC_BOMB_NOISE ,
								    Sound::NOISE, false,
								    this->channel10_);
  this->listSound_[Sound::REBON_BOMB_NOISE] = new Fmod::FmodSound(this->sys_,
								  "./ressources/sounds/boing.MP3",
								  Sound::REBON_BOMB_NOISE,
								  Sound::NOISE, false,
								  this->channel11_);

  this->listSound_[Sound::FUFU_CORKI_BOMB_NOISE] = new Fmod::FmodSound(this->sys_,
								  "./ressources/sounds/HunCorki.mp3",
								  Sound::FUFU_CORKI_BOMB_NOISE,
								  Sound::NOISE, false,
								  this->channel12_);
  this->listSound_[Sound::FUFU_CHOGATH_BOMB_NOISE] = new Fmod::FmodSound(this->sys_,
								  "./ressources/sounds/HunCho.mp3",
								  Sound::FUFU_CHOGATH_BOMB_NOISE,
								  Sound::NOISE, false,
								  this->channel14_);
  this->listSound_[Sound::FUFU_NOCTURNE_BOMB_NOISE] = new Fmod::FmodSound(this->sys_,
								  "./ressources/sounds/HunNocturne.mp3",
								  Sound::FUFU_NOCTURNE_BOMB_NOISE,
								  Sound::NOISE, false,
								  this->channel15_);
  this->listSound_[Sound::FUFU_RYZE_BOMB_NOISE] = new Fmod::FmodSound(this->sys_,
								  "./ressources/sounds/HunRyze.mp3",
								  Sound::FUFU_RYZE_BOMB_NOISE,
								  Sound::NOISE, false,
								  this->channel16_);
  this->listSound_[Sound::FUFU_FIDDLESTICK_BOMB_NOISE] = new Fmod::FmodSound(this->sys_,
								  "./ressources/sounds/HunFiddle.mp3",
								  Sound::FUFU_FIDDLESTICK_BOMB_NOISE,
								  Sound::NOISE, false,
								  this->channel17_);

  this->listSound_[Sound::MISSILE_BOMB_NOISE] = new Fmod::FmodSound(this->sys_,
								  "./ressources/sounds/missile.mp3",
								  Sound::MISSILE_BOMB_NOISE,
								  Sound::NOISE, false,
								  this->channel13_);
  this->listSound_[Sound::CORKI_SKILL_VOICE] = new Fmod::FmodSound(this->sys_,
								  "./ressources/sounds/UltCorki.mp3",
								  Sound::CORKI_SKILL_VOICE,
								  Sound::VOICE, false,
								  this->channel5_);
  this->listSound_[Sound::CHOGATH_SKILL_VOICE] = new Fmod::FmodSound(this->sys_,
								  "./ressources/sounds/UltCho.mp3",
								  Sound::CHOGATH_SKILL_VOICE,
								  Sound::VOICE, false,
								  this->channel6_);
  this->listSound_[Sound::RYZE_SKILL_VOICE] = new Fmod::FmodSound(this->sys_,
								  "./ressources/sounds/UltRyze.mp3",
								  Sound::RYZE_SKILL_VOICE,
								  Sound::VOICE, false,
								  this->channel7_);
  this->listSound_[Sound::NOCTURNE_SKILL_VOICE] = new Fmod::FmodSound(this->sys_,
								  "./ressources/sounds/UltNocturne.mp3",
								  Sound::NOCTURNE_SKILL_VOICE,
								  Sound::VOICE, false,
								  this->channel8_);
  this->listSound_[Sound::FIDDLE_SKILL_VOICE] = new Fmod::FmodSound(this->sys_,
								  "./ressources/sounds/UltFiddle.mp3",
								  Sound::FIDDLE_SKILL_VOICE,
								  Sound::VOICE, false,
								  this->channel9_);

  this->listSound_[Sound::CORKI_DMG_VOICE] = new Fmod::FmodSound(this->sys_,
								  "./ressources/sounds/dmgCorki.mp3",
								  Sound::CORKI_DMG_VOICE,
								  Sound::VOICE, false,
								  this->channel18_);
  this->listSound_[Sound::CHOGATH_DMG_VOICE] = new Fmod::FmodSound(this->sys_,
								  "./ressources/sounds/dmgCho.mp3",
								  Sound::CHOGATH_DMG_VOICE,
								  Sound::VOICE, false,
								  this->channel19_);
  this->listSound_[Sound::FIDDLE_DMG_VOICE] = new Fmod::FmodSound(this->sys_,
								  "./ressources/sounds/dmgFiddle.mp3",
								  Sound::FIDDLE_DMG_VOICE,
								  Sound::VOICE, false,
								  this->channel20_);
  this->listSound_[Sound::RYZE_DMG_VOICE] = new Fmod::FmodSound(this->sys_,
								  "./ressources/sounds/dmgRyze.mp3",
								  Sound::RYZE_DMG_VOICE,
								  Sound::VOICE, false,
								  this->channel21_);
  this->listSound_[Sound::NOCTURNE_DMG_VOICE] = new Fmod::FmodSound(this->sys_,
								  "./ressources/sounds/dmgNocturne.mp3",
								  Sound::NOCTURNE_DMG_VOICE,
								  Sound::VOICE, false,
								  this->channel22_);
  this->volume_[Sound::AMBIANCE] = music;
  this->volume_[Sound::NOISE] = noise;
  this->volume_[Sound::VOICE] = voice;
}

Fmod::FmodManager::~FmodManager()
{}

void		Fmod::FmodManager::playSound(Sound::e_sound sound)
{
  FmodSound	*my_sound = this->listSound_[sound];

  /*   Ancienne version !
  **   //FMODError(this->sys_->playSound(FMOD_CHANNEL_FREE, my_sound->fsound_, true, &my_sound->channel_));
  */
  FMODError(this->sys_->playSound(my_sound->fsound_, NULL, true, &my_sound->channel_));
  if (Sound::AMBIANCE == my_sound->type_)
    {
      my_sound->channel_->setVolume((float)((this->volume_[Sound::AMBIANCE] / 100.0)));
      my_sound->channel_->setPaused(false);
    }
  if (Sound::NOISE == my_sound->type_)
    {
      my_sound->channel_->setVolume((float)((this->volume_[Sound::NOISE] / 100.0)));
      my_sound->channel_->setPaused(false);
    }
  if (Sound::VOICE == my_sound->type_)
    {
      my_sound->channel_->setVolume((float)((this->volume_[Sound::VOICE] / 100.0)));
      my_sound->channel_->setPaused(false);
    }
}



void		Fmod::FmodManager::changeVol(Sound::e_soundType type, int volume)
{
  this->volume_[type] = volume;
  changeVolAmbiance();
  changeVolNoise();
  changeVolVoice();
}

void		Fmod::FmodManager::changeVolAmbiance()
{
  std::map<Sound::e_sound, Fmod::FmodSound *>::iterator it;

  for (it = this->listSound_.begin(); it != this->listSound_.end(); ++it)
    {
      FmodSound	*my_sound= it->second;
      if (my_sound->type_ == Sound::AMBIANCE && !(my_sound->channel_ != 0))
	{
	  my_sound->channel_->setPaused(true);
	  my_sound->channel_->setVolume((float)((this->volume_[Sound::AMBIANCE] / 100.0)));
	  my_sound->channel_->setPaused(false);
	}
    }
}

void		Fmod::FmodManager::changeVolNoise()
{
  std::map<Sound::e_sound, Fmod::FmodSound *>::iterator it;

  for (it = this->listSound_.begin(); it != this->listSound_.end(); ++it)
    {
      FmodSound	*my_sound= it->second;
      if (my_sound->type_ == Sound::NOISE && !(my_sound->channel_ != 0))
	{
	  my_sound->channel_->setPaused(true);
	  my_sound->channel_->setVolume((float)((this->volume_[Sound::NOISE] / 100.0)));
	  my_sound->channel_->setPaused(false);
	}
    }
}

void		Fmod::FmodManager::changeVolVoice()
{
  std::map<Sound::e_sound, Fmod::FmodSound *>::iterator it;

  for (it = this->listSound_.begin(); it != this->listSound_.end(); ++it)
    {
      FmodSound	*my_sound= it->second;
      if (my_sound->type_ == Sound::VOICE  && !(my_sound->channel_ != 0))
	{
	  my_sound->channel_->setPaused(true);
	  my_sound->channel_->setVolume((float)((this->volume_[Sound::VOICE] / 100.0)));
	  my_sound->channel_->setPaused(false);
	}
    }
}

void		Fmod::FmodManager::stopSound(Sound::e_sound song)
{
  std::map<Sound::e_sound, Fmod::FmodSound *>::iterator it;

  for (it = this->listSound_.begin(); it != this->listSound_.end(); ++it)
    {
      FmodSound	*my_sound= it->second;
      if (my_sound->sound_ == song)
	my_sound->channel_->setPaused(true);
    }
}

void		Fmod::FmodManager::FMODError(FMOD_RESULT res)
{
  if (res != FMOD_OK)
    {
      std::cout << "FMOD error: " << FMOD_ErrorString(res) << std::endl;
    }
}
