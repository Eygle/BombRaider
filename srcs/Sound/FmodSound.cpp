#include <iostream>
#include <stdio.h>

#include "Sound/FmodSound.hpp"
#include "fmodex/fmod.hpp"

Fmod::FmodSound::FmodSound(FMOD::System *sys, std::string const& soundPath, Sound::e_sound sound, Sound::e_soundType type, bool loop, FMOD::Channel *channel)
  : sys_(sys), soundPath_(soundPath), sound_(sound), type_(type)
{
  this->channel_ =channel;
  this->loop_ = loop;
  FMODError(this->sys_->createStream(this->soundPath_.c_str(),
			  FMOD_DEFAULT,
			  0,
			  &this->fsound_));
}

Fmod::FmodSound::~FmodSound()
{
  std::cout << "fin sound" << std::endl;
  // this->fsound_->release();
}

void            Fmod::FmodSound::FMODError(FMOD_RESULT res)
{
  if (res != FMOD_OK)
    {
      std::cout << "FMOD error: " << FMOD_ErrorString(res) << std::endl;
      exit(42);
    }
}
