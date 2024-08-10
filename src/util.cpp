#include "util.hpp"

namespace Util {
  std::vector<std::string_view> splitOn(std::string_view str, std::string_view delimiter) {
      std::vector<std::string_view> result;
      size_t start = 0;
      size_t end = str.find(delimiter);
      while (end != std::string::npos) {
          std::string_view token = str.substr(start, end - start);
          if (!token.empty()) {
              result.push_back(token);
          }
          start = end + delimiter.length();
          end = str.find(delimiter, start);
      }
      std::string_view token = str.substr(start);
      if (!token.empty()) {
          result.push_back(token);
      }
      return result;
  }
}