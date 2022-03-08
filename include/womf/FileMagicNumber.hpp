#ifndef WOMF_FILEMAGICNUMBER_HPP_
#define WOMF_FILEMAGICNUMBER_HPP_

#include <string>

namespace womf {

  class FileMagicNumber final {
    public:
      FileMagicNumber();
      ~FileMagicNumber();

      static std::string getMagicNumber(const std::string& fileName, const std::size_t bufferSize);

    private:
      static constexpr char HEX[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  };

} /* namespace womf */

#endif /* WOMF_FILEMAGICNUMBER_HPP_ */
