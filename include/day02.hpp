#pragma once

#include <vector>
#include <string>
#include <array>

namespace Day02 {

typedef std::array<u_int32_t, 3> Drawing;
typedef std::vector<Drawing> Drawings;
typedef std::vector<std::string> Strings;

struct Game {
  int id;
  Drawings drawings;
};

typedef std::vector<Game> Games;

struct Puzzle {
  Drawing maxCounts;
  Games games;
};

const Puzzle parse(const u_int32_t maxRed, const u_int32_t maxGreen, const u_int32_t maxBlue, const std::string& filename);

const u_int32_t part1(const Puzzle& puz);

const size_t part2(const Puzzle& puz);
}