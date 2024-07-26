#pragma once

#include <cstring>
#include <sys/types.h>
#include <array>
#include <string>

namespace Day01 {

/// Makes the reverse of each string in an array of strings
template<int N>
void mkReverses(const std::array<std::string, N>& source, std::array<std::string, N>& target) {
  for(size_t i = 0; i < source.size(); ++i) {
    target[i] = std::string(source[i].rbegin(), source[i].rend());
  }
}

/// extract a number from a string according to the rules of part 1
u_int32_t numFromStringP1(const char* str);

// finds the first digit of a string given the candidates
char firstDigitOf(const std::array<std::string, 19>& candidates, const std::string& str);

/// extract a number from a string according to the rules of part 2
u_int32_t numFromStringP2( std::array<std::string, 19> smun, const std::string& str);

// returns the solution to part 1
u_int32_t part1(std::string filename);

/// Returns the solution to part 2
u_int32_t part2(std::string filename);

}