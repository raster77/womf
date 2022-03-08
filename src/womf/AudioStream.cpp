#define STB_VORBIS_HEADER_ONLY
#include "womf/miniaudio/stb_vorbis.c"
#undef STB_VORBIS_HEADER_ONLY
#include "womf/AudioStream.hpp"
#include "womf/FileMagicNumber.hpp"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <ios>
#include <sstream>
#include <vector>

namespace womf {

  AudioStream::AudioStream()
    : mInitialized(false)
    , mFile("")
    , mAudioFormat(UNSUPPORTED)
    , mState(STOP)
    , mDuration(0.f)
    , mLoop(false) {
    mStreamData.enginePtr = getAudioEngine();
    mStreamData.streamPtr = this;
    if (getAudioEngine()->pDevice->onData == nullptr) {
      getAudioEngine()->pDevice->onData = audioCallback;
    }
    getAudioEngine()->pDevice->pUserData = &mStreamData;
  }

  AudioStream::~AudioStream() {
    uninitialize();
  }

  void AudioStream::audioCallback(ma_device* devicePtr, void* outputPtr, const void* inputPtr, ma_uint32 frameCount) {
    StreamData *streamDataPtr = static_cast<StreamData*>(devicePtr->pUserData);
    ma_engine_read_pcm_frames(streamDataPtr->enginePtr, outputPtr, frameCount, nullptr);
  }

  void AudioStream::uninitialize() {
    ma_sound_uninit(&mSound);
  }

  bool AudioStream::load(const std::string& fileName, const bool stream, const bool pitch, const bool spatialization) {
    if (std::filesystem::exists(fileName)) {
      if (mInitialized) {
        uninitialize();
      }

      mAudioFormat = getAudioFormat(fileName);
      if (mAudioFormat != AudioFormat::UNSUPPORTED) {
        const uint32_t streamFlag = stream ? MA_SOUND_FLAG_STREAM : 0;
        const uint32_t pitchFlag = pitch ? 0 : MA_SOUND_FLAG_NO_PITCH;
        const uint32_t spatializationFlag = spatialization ? 0 : MA_SOUND_FLAG_NO_SPATIALIZATION;

        mFile = fileName;
        uint32_t flags = streamFlag | pitchFlag | spatializationFlag;
        ma_sound_init_from_file(getAudioEngine(), mFile.c_str(), flags, nullptr, nullptr, &mSound);
        ma_sound_set_looping(&mSound, mLoop);
        setAudioInfos();
        mInitialized = true;
        return true;
      }
    }
    return false;
  }

  void AudioStream::play() {
    if (mInitialized) {
      ma_result res = ma_sound_start(&mSound);
      mState = res != MA_SUCCESS ? AudioStreamState::STOP : AudioStreamState::PLAY;
    }
  }

  void AudioStream::pause() {
    if (mState == AudioStreamState::PLAY) {
      ma_sound_stop(&mSound);
      mState = AudioStreamState::PAUSE;
    }
  }

  void AudioStream::stop() {
    if (mState == AudioStreamState::PLAY || mState == AudioStreamState::PAUSE) {
      ma_sound_stop(&mSound);
      ma_sound_seek_to_pcm_frame(&mSound, 0);
      mState = AudioStreamState::STOP;
    }
  }

  void AudioStream::seek(const int ms) {
    if (mInitialized) {
      const int sign = ms >= 0 ? 1 : -1;
      const unsigned int seekSize = ma_calculate_buffer_size_in_frames_from_milliseconds(static_cast<uint32_t>(std::abs(ms)), getSampleRate());
      long long unsigned int cursor;
      ma_sound_get_cursor_in_pcm_frames(&mSound, &cursor);
      ma_sound_seek_to_pcm_frame(&mSound, cursor + seekSize * sign);
    }
  }

  void AudioStream::seekTo(const unsigned int posMs) {
    const unsigned int seekSize = ma_calculate_buffer_size_in_frames_from_milliseconds(posMs, getSampleRate());
    ma_sound_seek_to_pcm_frame(&mSound, seekSize);
  }

  void AudioStream::setLooping(const bool loop) {
    mLoop = loop;
    if (mInitialized) {
      ma_sound_set_looping(&mSound, mLoop);
    }
  }

  float AudioStream::getAudioPosition() {
    float cursor = 0.f;
    if (mInitialized) {
      ma_sound_get_cursor_in_seconds(&mSound, &cursor);
    }
    return cursor;
  }

  void AudioStream::setAudioInfos() {
    if (mAudioFormat == AudioFormat::OGG) {
      setVorbisDuration();
    } else {
      ma_sound_get_length_in_seconds(&mSound, &mDuration);
    }
  }

  void AudioStream::setVorbisDuration() {
    int error = 0;
    stb_vorbis *vorbis = stb_vorbis_open_filename(mFile.c_str(), &error, nullptr);
    mDuration = stb_vorbis_stream_length_in_seconds(vorbis);
    stb_vorbis_close(vorbis);
  }

  AudioFormat AudioStream::getAudioFormat(const std::string& fileName) {
    const std::string sig = FileMagicNumber::getMagicNumber(fileName, 8);

    if (sig.substr(0, 6) == "494433") {
      return AudioFormat::MP3;
    }
    else if (sig == "664C614300000022") {
      return AudioFormat::FLAC;
    }
    else if (sig == "4F67675300020000") {
      return AudioFormat::OGG;
    }
    else if (sig.substr(0, 8) == "52494646") {
      return AudioFormat::WAVE;
    }
    return AudioFormat::UNSUPPORTED;
  }

} /* namespace womf */
