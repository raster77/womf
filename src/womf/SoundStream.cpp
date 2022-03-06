#include "SoundStream.hpp"

namespace womf {

  SoundStream::SoundStream()
    : AudioStream()
  {
  }

  SoundStream::~SoundStream()
  {
  }

  bool SoundStream::loadFromFile(const std::string& fileName, const bool stream) {
    return load(fileName, stream, true, true);
  }

} /* namespace womf */
