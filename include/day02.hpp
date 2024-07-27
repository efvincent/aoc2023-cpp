#pragma once

#include <vector>
#include <string>
#include <array>

namespace Day02 {

using Drawing = std::array<u_int32_t, 3>;
using Drawings = std::vector<Drawing>;
using Strings = std::vector<std::string>;

struct Game {
  int id;
  Drawings drawings;
};

typedef std::vector<Game> Games;

struct Puzzle {
  Drawing maxCounts;
  Games games;
};

uint part1(const Puzzle& puz);

uint part2(const Puzzle& puz);
}