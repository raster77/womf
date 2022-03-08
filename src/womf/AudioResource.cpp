#define MA_NO_ENCODING
#define MA_NO_GENERATION

#define STB_VORBIS_HEADER_ONLY
#include "womf/miniaudio/stb_vorbis.c"

#define MINIAUDIO_IMPLEMENTATION
#include "womf/miniaudio/miniaudio.h"

#undef STB_VORBIS_HEADER_ONLY
#include "womf/miniaudio/stb_vorbis.c"

#include "womf/AudioResource.hpp"
#include <stdexcept>
#include <memory>
#include <atomic>

namespace womf {

  namespace {
    std::atomic<unsigned int> refCount(0);
    std::unique_ptr<ma_engine> audioEngine;
  }

  AudioResource::AudioResource()
    : mChannels(0)
    , mSampleRate(0)
    , mMasterVolume(0.f) {

    if (refCount == 0) {
      audioEngine = std::make_unique<ma_engine>();

      if (ma_engine_init(nullptr, audioEngine.get()) != MA_SUCCESS) {
        throw std::runtime_error("Failed to initialize audio engine");
      }

      audioEngine.get()->pDevice->onData = nullptr;

      mChannels = ma_engine_get_channels(audioEngine.get());
      mSampleRate = ma_engine_get_sample_rate(audioEngine.get());
    }

    refCount++;
  }

  AudioResource::~AudioResource() {
    // Decrement resources counter
    refCount--;

    // If there's no more resource alive, we can destroy the device
    if (refCount == 0) {
      ma_engine_uninit(audioEngine.get());
    }
  }

  const unsigned int AudioResource::getChannels() const {
    return mChannels;
  }

  const unsigned int AudioResource::getSampleRate() const {
    return mSampleRate;
  }

  const float AudioResource::getMasterVolume() const {
    return mMasterVolume;
  }

  void AudioResource::setMasterVolume(const float masterVolume) {
    if (audioEngine) {
      mMasterVolume = masterVolume;
      ma_engine_set_volume(audioEngine.get(), mMasterVolume);
    }
  }

  ma_engine* AudioResource::getAudioEngine() {
    return audioEngine.get();
  }

} /* namespace womf */
