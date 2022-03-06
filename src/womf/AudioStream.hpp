#ifndef WOMF_AUDIOSTREAM_HPP_
#define WOMF_AUDIOSTREAM_HPP_

#include "AudioResource.hpp"
#include "AudioFormat.hpp"
#include "AudioStreamState.hpp"
#include "miniaudio/miniaudio.h"
#include <memory>
#include <string>

namespace womf {

  class AudioStream : public AudioResource {
    public:
      AudioStream();
      virtual ~AudioStream();

      /**
       * @brief Load an audio file
       *
       * @param fileName file to load
       * @param stream if true, stream from file else load file entirely
       * @param pitch enable pitch
       * @param spatialization enable spatialization
       * @return true on success
       */
      virtual bool loadFromFile(const std::string& fileName, const bool stream = true) = 0;

      /**
       * @brief File name
       *
       * @return
       */
      const std::string& getFileName() {
        return mFile;
      }

      /**
       * @brief Audio format of the file
       *
       * @return
       */
      const AudioFormat& getAudioFormat() {
        return mAudioFormat;
      }

      /**
       * @brief Play the current audio file
       *
       */
      void play();

      /**
       * @brief Pause the current audio file
       *
       */
      void pause();

      /**
       * @brief Stop the current audio file
       *
       */
      void stop();

      /**
       * @brief Seek from current position
       *
       * @param ms milliseconds to seek
       */
      void seek(const int ms);

      /**
       * @brief Seek to position
       *
       * @param posMs position in milliseconds
       */
      void seekTo(const unsigned int posMs);

      /**
       * @brief Duration of audio
       *
       * @return
       */
      const float getDuration() {
        return mDuration;
      }

      /**
       * @brief Position in second of playing audio
       *
       * @return position
       */
      float getAudioPosition();

      /**
       * @brief State of music
       *
       * @return AudioStreamState
       */
      const AudioStreamState getState() {
        return mState;
      }

      /**
       * @brief Enable or disable sound looping
       *
       * @param loop
       */
      void setLooping(const bool loop);

      /**
       * @brief Looping enabled or not
       *
       * @param loop
       */
      const bool isLooping() {
        return mLoop;
      }

    protected:
      /**
       * @brief Internal data for audio callback
       *
       */
      struct StreamData {
          ma_engine *enginePtr;
          AudioStream *streamPtr;

          StreamData()
              : enginePtr(nullptr), streamPtr(nullptr) {
          }
      };

      ma_sound mSound;
      bool mInitialized;
      std::string mFile;
      AudioFormat mAudioFormat;
      AudioStreamState mState;
      float mDuration;
      bool mLoop;
      StreamData mStreamData;

      bool load(const std::string& fileName, const bool stream, const bool pitch, const bool spatialization);
      void uninitialize();
      void setAudioInfos();
      void setVorbisDuration();
      AudioFormat getAudioFormat(const std::string& fileName);

      static void audioCallback(ma_device* devicePtr, void* outputPtr, const void* inputPtr, ma_uint32 frameCount);
  };

} /* namespace womf */

#endif /* WOMF_AUDIOSTREAM_HPP_ */
