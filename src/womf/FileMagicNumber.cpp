#include "FileMagicNumber.hpp"
#include <fstream>
#include <iomanip>
#include <ios>
#include <vector>

namespace womf {

  FileMagicNumber::FileMagicNumber() {}

  FileMagicNumber::~FileMagicNumber() {}

  std::string FileMagicNumber::getMagicNumber(const std::string& fileName, const std::size_t bufferSize) {

    std::fstream file(fileName, std::ios_base::binary | std::ios_base::in | std::ios_base::out);
    std::vector<char> buff(bufferSize, 0);
    file.read(&buff[0], bufferSize);
    file.close();

    std::string str;
    str.reserve(buff.size() * 2);

    for (auto &c : buff) {
      str.append(&HEX[(c & 0xF0) >> 4], 1);
      str.append(&HEX[c & 0xF], 1);
    }
    return str;

  }

} /* namespace womf */
