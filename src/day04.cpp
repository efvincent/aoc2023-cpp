#include "day04.hpp"
#include <algorithm>
#include <cctype>
#include <iterator>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <vector>
#include <fstream>
#include "util.hpp"
#include <set>
#include <map>

namespace Day04 {

using strings = std::vector<std::string>;
using str     = std::string;
using ints    = std::vector<int>;
using intSet  = std::set<int>;

struct Card {
  int id;
  intSet game_nums;
  intSet winning_nums;
  int copies{1};
  uint score{0};
};

using Puzzle = std::vector<Card>;

Card parseLine(str line) {
  std::vector<std::string_view> split1 = Util::splitOn(line, str("|"));       
  std::vector<std::string_view> split2 = Util::splitOn(split1[0], str(":"));

  int id = std::stoi(split2[0].substr(5).data()) - 1;
  intSet nums, wins;
  for (const auto& s : Util::splitOn(split2[1], " ")) {
    wins.insert(std::stoi(s.data()));
  }
  for (const auto& s : Util::splitOn(split1[1], " ")) {
    nums.insert(std::stoi(s.data()));
  }
  return Card{ id, nums, wins};
}

Puzzle parse(str filename) {
  std::ifstream file{filename};
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file " + filename);
  } 
  str line;
  Puzzle puz;
  while (std::getline(file, line)) {
    puz.push_back(parseLine(line));
  }
  return puz;  
}

uint calcAns(int count) {
  static std::map<int, uint> memoized;
  auto found = memoized.find(count);
  if (found != memoized.end()) {
    return found->second;
  } else {
    uint total{0};
    if (count == 1) { 
      total = 1;
    } else {
      for (uint i = 1; i < count; i++) {
        total = (total == 0 ? 1 : total) * 2;
      }
    }
    memoized[count] = total;
    return total;
  }
}

void addCount(Puzzle& puz, const int startIdx, const int count, const int inc) {
  // add one to each card count starting at startIdx and going for count cards
  for(int i = startIdx; i < startIdx + count; i++) {
    if (i < puz.size()) {
      puz[i].copies+= inc;
    }
  }
}

uint compute_answer(Puzzle& puz) { 
  uint total_score{0};
  for (auto& card : puz) {
    std::vector<int> intersections;
    std::set_intersection(card.game_nums.begin(), card.game_nums.end(),
      card.winning_nums.begin(), card.winning_nums.end(), std::back_inserter(intersections));
    int num_wins = intersections.size();
    card.score = calcAns(num_wins);
    total_score += card.score;
    addCount(puz, card.id + 1, num_wins, card.copies);
  }
  return total_score;
}

std::pair<int, int> solve(const std::string& filename) {
  Puzzle puz = parse(filename);
  int part1 = compute_answer(puz);
  int part2{0};
    for(const auto& card : puz) {
    part2 += card.copies;
  }
  return std::pair(part1, part2);
}

} // namespace day03
