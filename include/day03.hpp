#pragma once

#include <vector>
#include <string>
#include <array>

namespace Day03 {

typedef std::array<u_int32_t, 3> Drawing;
typedef std::vector<Drawing> Drawings;
typedef std::vector<std::string> Strings;

struct Game {
  int id;
  Drawings drawings;
};

typedef std::vector<Game> Games;

const u_int32_t part1(const std::string& filename);

const u_int32_t part2(const std::string& filename);
}
