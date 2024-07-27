#pragma once

#include <cstring>
#include <sys/types.h>
#include <array>
#include <string>

namespace Day01 {

#define STR_ARRAY(n) std::array<std::string, n>

/// Makes the reverse of each string in an array of strings
template<int N>
void mkReverses(const STR_ARRAY(N)& source, STR_ARRAY(N)& target) {
  for(size_t i = 0; i < source.size(); ++i) {
    target[i] = std::string(source[i].rbegin(), source[i].rend());
  }
}

// returns the solution to part 1
uint part1(std::string filename);

/// Returns the solution to part 2
uint part2(std::string filename);

}