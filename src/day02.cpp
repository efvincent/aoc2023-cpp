#include "day02.hpp"
#include "util.hpp"
#include <algorithm>
#include <array>
#include <cstddef>
#include <sys/types.h>
#include <utility>

namespace Day02 {

const std::pair<u_int32_t, u_int32_t> parseCubeCount(const std::string& handStr) {
  // example: handStr = "3 blue"
  // index of a color is the length of the colors string minus 3
  // red = 0
  // blue = 1
  // green = 2
  auto cubCountParts = Util::splitOn(handStr, " ");
  return std::pair(cubCountParts[1].size() - 3, std::stoi(cubCountParts[0]));
}

const Drawing parseDrawing(const std::string& drawingStr) {
  // example: handsStr = 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
  auto cubeCountStrs = Util::splitOn(drawingStr, ", ");
  Drawing drawing{0,0,0};
  for (std::string cubeCountStr : cubeCountStrs) {
    auto [idx, count] = parseCubeCount(cubeCountStr);
    drawing[idx] = count;
  }
  return drawing;
}

const Game parseGame(const std::string& line) {
  // line = "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green"
  auto lineParts = Util::splitOn(line, ": ");
  auto gameNumParts = Util::splitOn(lineParts[0], " ");
  auto gameNum = std::stoi(gameNumParts[1]);

  std::string handsStr =
      lineParts[1]; // = "3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green"
  Strings handsStrParts = Util::splitOn(handsStr, "; ");
  Drawings hands;
  for (std::string handStrs : handsStrParts) {
    auto hand = parseDrawing(handStrs);
    hands.push_back(hand);
  }

  return Game{gameNum, hands};
}

const Puzzle parse(const u_int32_t maxRed, const u_int32_t maxGreen, const u_int32_t maxBlue,
                   const std::string &filename) {
  auto games = Util::importFile<Game>(filename, parseGame);
  Puzzle puz{{maxRed, maxBlue, maxGreen}, games};
  return puz;
}

const bool possible(const Drawing& max, const Drawings& drawings) {
  for (const auto& drawing : drawings) {
    if (drawing[0] > max[0] || drawing[1] > max[1] || drawing[2] > max[2]) {
      return false;
    }
  }
  return true;
}

const u_int32_t part1(const Puzzle& puz) {
  u_int32_t total = 0;
  for (const auto& game : puz.games) {
    total += possible(puz.maxCounts, game.drawings) ? game.id : 0;
  }
  return total;
}

const size_t part2(const Puzzle& puz) {
  size_t total(0);
  for(const auto& game : puz.games) {
    Drawing max{0,0,0};
    for(const auto& drawing : game.drawings) {
      for (int i = 0; i < 3; i++)
        max[i] = std::max(max[i], drawing[i]);
    }
    total += max[0] * max[1] * max[2];
  }
  return total;
}

} // namespace Day02