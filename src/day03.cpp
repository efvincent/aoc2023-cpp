#include "day03.hpp"
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <vector>
#include <fstream>
#include "vec.hpp"

namespace Day03 {

enum class AOC_PART { One, Two };

struct Part {
  BoundingBox bbox;
  int num = 0;
};

struct Puzzle {
  Puzzle() = delete;
  Puzzle(std::vector<char>&& data, BoundingBox bbox, std::vector<Vec2>&& symbols, 
        std::vector<Part>&& parts) : 
          data(std::move(data)), 
          bbox(std::move(bbox)), 
          symbols(std::move(symbols)), 
          parts(std::move(parts)) { }

  std::vector<char> data;
  BoundingBox bbox;
  std::vector<Vec2> symbols;
  std::vector<Part> parts;

  char get(int x, int y) const;
  bool isValidPart(Part& part);
};

std::ostream& operator<<(std::ostream& os, const Part& p) {
  os << p.num; 
  return os;
}

char Puzzle::get(int x, int y) const {
  if (!bbox.isPointInBox(Vec2{x,y}))
    throw std::runtime_error("Puzzle index out of bounds");
  return data[y * (bbox.lowerRight.x + 1) + x];
}

bool Puzzle::isValidPart(Part& part) {
  // clip the bounding box to the dimensions of the puzzle so
  // we don't attempt to index outside of range
  BoundingBox::clipTo(part.bbox, bbox);

  // Lambda to check if a part is valid
  bool isValid = false;
  auto isValidPart = [this, &isValid](const Vec2& pos) -> bool {
    char c = get(pos.x, pos.y);
    if (c != '.' && !(c >= '0' && c <= '9')) {
      isValid = true;
      return false;   // short circuit forEachpoint
    }
    return true;      // keep checking
  };    

  part.bbox.forEachPoint(isValidPart);
  return isValid;
}  

void addPart(std::vector<Part>& parts, const std::vector<char>& numStr, int nStart, int height, int width) {
  int number = std::stoi(numStr.data());
  BoundingBox bb{Vec2{nStart - 1, height - 1}, Vec2{nStart + width, height + 1}};
  Part p{std::move(bb), number};
  parts.push_back(std::move(p));
}

/// Get the dimensions (x,y) of the data in the file. Will be used
/// to determine the stride
const Puzzle parse(const std::string& filename, const AOC_PART questionPart = AOC_PART::One) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file " + filename);
  }
  int width = 0, height = 0, nStart = 0;
  bool inNum = false;
  std::string line;
  std::vector<char> contents; 
  std::vector<char> numStr;
  std::vector<Part> parts;
  std::vector<Vec2> symbols;

  while (std::getline(file,line)) {
    width = line.length();
    contents.insert(contents.end(), line.begin(), line.end());
    if (inNum) {
      addPart(parts, numStr, nStart, height - 1, numStr.size() + 1);
      numStr = std::vector<char>();
      inNum = false;
    }

    for(int x = 0; x < line.length(); x++) {
      char cur = line[x];
      if (std::isdigit(cur)) {
        if (!inNum) nStart = x;
        numStr.push_back(cur);
        inNum = true;
      } else {
        if (inNum) {
          addPart(parts, numStr, nStart, height, numStr.size());
          numStr = std::vector<char>();
          inNum = false;
        }
        inNum = false;
        if ((questionPart == AOC_PART::One && cur != '.') 
         || (questionPart == AOC_PART::Two && cur == '*')) {
          symbols.push_back(Vec2{x, height});
        }
      }
    }
    ++height;
  }
  // if there's a number in the lower right corner, inNum will be true. Capture
  // this last number
  if (inNum) {
      addPart(parts, numStr, nStart, height - 1, numStr.size() + 1);
  }

  file.close();
  auto bb = BoundingBox{Vec2{0,0}, Vec2{width - 1, height - 1}};
  return Puzzle(std::move(contents), std::move(bb), std::move(symbols), std::move(parts));
}

uint part1(const std::string& filename) {  // 535235
  Puzzle puz = parse(filename);
  unsigned int total{0};
  for (Part& p : puz.parts) {
    if (puz.isValidPart(p)) {
      total += p.num;
    } 
  }
  return total;
}

const uint partScore(const Puzzle& puz, const Vec2& gear) {
  // run through all the parts, see which are next to gear
  uint total = 1;
  int count = 0;
  for (const Part& p : puz.parts) {
    if (p.bbox.isPointInBox(gear)) {
      count++;
      total *= p.num;
    }
  }
  if (count == 2) {
    return total;
  }
  return 0;
}

uint part2(const std::string& filename) {
  // run through every symbol, check what distinct numbers they border
  // if #distinct borders = 2, mult them and add to the total
  Puzzle puz = parse(filename, AOC_PART::Two);
  uint total{0};
  for (Vec2 gear : puz.symbols) {
    total += partScore(puz, gear);
  }
  return total;
}

} // namespace day03
