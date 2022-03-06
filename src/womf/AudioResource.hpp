#ifndef WOMF_AUDIORESOURCE_HPP_
#define WOMF_AUDIORESOURCE_HPP_

#include "miniaudio/miniaudio.h"

namespace womf {

  class AudioResource {
    public:
      AudioResource();
      ~AudioResource();

      /**
       * @brief Audio device channels
       *
       * @return Number of channels
       */
      const unsigned int getChannels() const;

      /**
       * @brief Audio device sample rate
       *
       * @return Sample rate
       */
      const unsigned int getSampleRate() const;

      /**
       * @brief Volume of audio device
       *
       * @return Volume from 0.0 to 1.0
       */
      const float getMasterVolume() const;

      /**
       * @brief Set volume of audio device
       *
       * @param masterVolume from 0.0 to 1.0
       */
      void setMasterVolume(const float masterVolume);

    protected:
      ma_engine* getAudioEngine();

    private:
      unsigned int mChannels;
      unsigned int mSampleRate;
      float mMasterVolume;
  };

} /* namespace womf */

#endif /* WOMF_AUDIORESOURCE_HPP_ */
