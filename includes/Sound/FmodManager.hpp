#ifndef __FMODMANAGER_HPP__
#define __FMODMANAGER_HPP__

#include <map>
#include "fmodex/fmod.hpp"
#include "fmodex/fmod_errors.h"
#include "FmodSound.hpp"
#include "ISoundManager.hpp"

namespace Fmod
{
  class FmodManager : public Sound::ISoundManager
  {
  private:
    FMOD::System	*sys_;

    FMOD::ChannelGroup *master;
    FMOD::ChannelGroup *channelBG_;
    FMOD::ChannelGroup *channelNoise_;
    FMOD::ChannelGroup *channelVoice_;
    //ambiance
    FMOD::Channel	*channel1_;
    FMOD::Channel	*channel2_;
    FMOD::Channel	*channel3_;
    FMOD::Channel	*channel4_;
    //voix
    FMOD::Channel	*channel5_;
    FMOD::Channel	*channel6_;
    FMOD::Channel	*channel7_;
    FMOD::Channel	*channel8_;
    FMOD::Channel	*channel9_;
    FMOD::Channel	*channel18_;
    FMOD::Channel	*channel19_;
    FMOD::Channel	*channel20_;
    FMOD::Channel	*channel21_;
    FMOD::Channel	*channel22_;
    //effet
    FMOD::Channel	*channel10_;
    FMOD::Channel	*channel11_;
    FMOD::Channel	*channel12_;
    FMOD::Channel	*channel13_;
    FMOD::Channel	*channel14_;
    FMOD::Channel	*channel15_;
    FMOD::Channel	*channel16_;
    FMOD::Channel	*channel17_;

    int			volume_[3];
    std::map<Sound::e_sound, Fmod::FmodSound *> listSound_;
  public:
    FmodManager(int, int, int);
    ~FmodManager();

  public:
    void FMODError(FMOD_RESULT res);
    void playSound(Sound::e_sound);

    void changeVol(Sound::e_soundType, int);
    void changeVolAmbiance();
    void changeVolNoise();
    void changeVolVoice();

    void stopSound(Sound::e_sound);
  };
};

#endif
