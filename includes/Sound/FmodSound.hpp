#ifndef __FMODSOUND_HPP__
#define __FMODSOUND_HPP__

#include <map>
#include <fmodex/fmod.hpp>
#include <fmodex/fmod_errors.h>
#include <string>
#include <stdlib.h>

#include "ISoundManager.hpp"

namespace Fmod
{
  class FmodSound
  {
  public:
    FMOD::System	*sys_;
    std::string		soundPath_;
    Sound::e_sound	sound_;
    Sound::e_soundType	type_;
    FMOD::Sound		*fsound_;
    FMOD::Channel	*channel_;
    bool		loop_;
  public:
    FmodSound(FMOD::System *, std::string const&, Sound::e_sound ,Sound::e_soundType, bool, FMOD::Channel*);
    FmodSound() {};
    ~FmodSound();
  public:
    void            FMODError(FMOD_RESULT res);
  };  
};

#endif
