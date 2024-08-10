#pragma once

#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <spdlog/spdlog.h>

namespace Util {

struct Timer {
  
  std::chrono::time_point<std::chrono::system_clock> start, end;
  std::chrono::duration<float> duration;
  std::string lbl;

  Timer() : Timer("Timer") {}

  Timer(std::string label) : lbl{label} {
    start = std::chrono::high_resolution_clock::now();
  }

  ~Timer() {
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    float ms = duration.count() * 1000.0f;
    spdlog::info("{}: {}ms", lbl, ms);
  }
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