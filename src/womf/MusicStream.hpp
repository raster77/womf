#ifndef WOMF_MUSICSTREAM_HPP_
#define WOMF_MUSICSTREAM_HPP_

#include "AudioStream.hpp"

namespace womf {

  class MusicStream : public AudioStream {
    public:
      MusicStream();
      ~MusicStream();

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

#endif /* WOMF_MUSICSTREAM_HPP_ */
