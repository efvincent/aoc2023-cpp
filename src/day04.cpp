#include "day04.hpp"
#include <array>
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <vector>
#include <fstream>
#include "vec.hpp"

namespace Day04 {

struct Spec {
  int cardIdLen{0};
  std::array<int, 2> valueCount{0, 0};
};

struct Puzzle {

};

Spec determineSpec(std::string sample) {
  return Spec{};
}

Puzzle parse(std::string filename) {
  return Puzzle{};  
}

uint part1(const std::string& filename) {
  return 0;
}

uint part2(const std::string& filename) {
  return 0;
}

} // namespace day03
