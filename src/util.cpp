#include "util.hpp"

namespace Util {

  Timer::Timer() {}

  Timer::~Timer() {}

  std::vector<std::string> splitOn(const std::string& str, const std::string& delimiter) {
      std::vector<std::string> result;
      size_t start = 0;
      size_t end = str.find(delimiter);
      while (end != std::string::npos) {
          result.push_back(str.substr(start, end - start));
          start = end + delimiter.length();
          end = str.find(delimiter, start);
      }
      result.push_back(str.substr(start));
      return result;
  }
}