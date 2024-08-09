#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <functional>

namespace Util {

class Timer {
public:
  Timer();
  ~Timer();
};

inline void line() { std::cout << "--------------------------------\n"; }

std::vector<std::string> getLines(std::string filename);


template<int N>
void mkReverses(const std::array<std::string, N>& source, std::array<std::string, N>& target) {
  for(size_t i = 0; i < source.size(); ++i) {
    target[i] = std::string(source[i].rbegin(), source[i].rend());
  }
}

template<typename T>
const std::vector<T> importFile(const std::string &filename, std::function<T(std::string)> fn) {
  std::ifstream file(filename);
  std::string line;
  std::vector<T> result;
  while(std::getline(file,line)) {
    T value = fn(line);
    result.emplace_back(value);
  }
  return result;
}
std::vector<std::string_view> splitOn(std::string_view str, std::string_view delimiter);

} // namespace Util