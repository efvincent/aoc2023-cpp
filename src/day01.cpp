#include "day01.hpp"
#include "util.hpp"

#include <fstream>
#include <cstring>
#include <functional>
#include <sys/types.h>
#include <array>
#include <optional>

namespace Day01 {

std::array<std::string, 19> nums = {
  "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
  "one", "two", "three", "four", "five", "six", "seven",
  "eight", "nine"
};

u_int32_t numFromStringP1(const char* str) {
  char s[3] = "xx";
  int len = strlen(str);
  for(size_t i = 0; i < len; i++) {
    if (!isdigit(str[i])) continue;
    if (s[0] == 'x') s[0] = str[i];
    s[1] = str[i];
  }
  return std::stoi(s); 
}

char firstDigitOf(const std::array<std::string, 19>& candidates, const std::string& str)  {
  std::optional<size_t> winner;
  char found = '\0';
  for (int candidateIdx = 0; candidateIdx < candidates.size(); candidateIdx++) {
    auto foundIdx = str.find(candidates[candidateIdx]);
    if (foundIdx != std::string::npos) {
      if (!winner || foundIdx < *winner)
      {
        winner = foundIdx;
        int n = candidateIdx > 9 ? candidateIdx - 9 : candidateIdx;
        found = n + '0';
      }
    }
  }
  return found;
}

u_int32_t numFromStringP2( std::array<std::string, 19> smun, const std::string& str) {
  std::string rts(std::string(str.rbegin(), str.rend()));
  char fst(firstDigitOf(nums, str));
  char snd(firstDigitOf(smun, rts));
  char s[3];
  s[0] = fst;
  s[1] = snd;
  return std::stoi(s); 
}

u_int32_t part1(std::string filename) {
  std::ifstream file(filename);
  u_int32_t total = 0;
  std::string line;
  while(std::getline(file, line)) {
    total += numFromStringP1(line.data());
  }
  return total;
}

u_int32_t part2(std::string filename) {
  std::array<std::string, 19> smun;
  mkReverses<19>(nums, smun);
  u_int32_t total = 0;

  Util::importFile<u_int32_t>(filename, [&total, &smun](const std::string& line) {
    return total += numFromStringP2(smun, line);
  });
  
  return total; 
}

}