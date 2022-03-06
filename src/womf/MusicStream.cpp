#include "MusicStream.hpp"

namespace womf {

  MusicStream::MusicStream()
    : AudioStream()
  {
  }

  MusicStream::~MusicStream()
  {
  }

  bool MusicStream::loadFromFile(const std::string& fileName, const bool stream) {
    return load(fileName, stream, false, false);
  }

} /* namespace womf */
