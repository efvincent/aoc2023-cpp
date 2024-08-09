#include <iostream>
#include <cstring>
#include <sys/types.h>
#include "day05.hpp"

int main(int argc, char** argv) {
  std::cout << "\033[2J";
  using namespace Day05;

  auto filename = argc == 2 ? argv[1] : "../data/d05.txt";

  auto [part1, part2] = solve(filename);

  std::cout << "part 1: " << part1 << "\n"
            << "part 2: " << part2 << std::endl;
  return 0;
}