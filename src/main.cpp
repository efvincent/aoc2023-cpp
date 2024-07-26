#include <iostream>
#include <cstring>
#include <sys/types.h>
#include "day03.hpp"

int main(int argc, char** argv) {

  using namespace Day03;

  auto filename = argc == 2 ? argv[1] : "../data/d03.txt";

  auto p1Ans = part1(filename);
  auto p2Ans = part2(filename);
  
  std::cout << "part 1: " << p1Ans << "\n";
  std::cout << "part 2: " << p2Ans << "\n";
  
  return 0;
}