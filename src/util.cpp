#include "util.hpp"

namespace Util {

  Timer::Timer() {}

  Timer::~Timer() {}

  std::vector<std::string> splitOn(const std::string& str, const std::string& delimiter) {
      std::vector<std::string> result;
      size_t start = 0;
      size_t end = str.find(delimiter);
      while (end != std::string::npos) {
          std::string token = str.substr(start, end - start);
          if (!token.empty()) {
              result.push_back(token);
          }
          start = end + delimiter.length();
          end = str.find(delimiter, start);
      }
      std::string token = str.substr(start);
      if (!token.empty()) {
          result.push_back(token);
      }
      return result;
  }
}