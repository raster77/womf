#ifndef WOMF_SOUNDSTREAM_HPP_
#define WOMF_SOUNDSTREAM_HPP_

#include "AudioStream.hpp"

namespace womf {

  class SoundStream final : public AudioStream {
    public:
      SoundStream();
      ~SoundStream();

      /**
       * @brief Load an audio file from disk
       *
       * @param fileName file name
       * @param stream Stream from disk if true, else load entire file in memory
       * @return True if no error, false otherwise
       */
      bool loadFromFile(const std::string& fileName, const bool stream = true) override;
  };

} /* namespace womf */

#endif /* WOMF_SOUNDSTREAM_HPP_ */
