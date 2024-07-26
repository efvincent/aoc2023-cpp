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

struct Part {
  Vec2 start;
  BoundingBox bbox;
  int len;
  int num;
};

std::ostream& operator<<(std::ostream& os, const Part& p) {
  os << p.num << "[" << p.len << "]" <<  " (" << p.start.x << "," << p.start.y << ")";
  return os;
}

struct Puzzle {
  std::vector<char> data;
  int stride;
  int lineCount;
  BoundingBox bbox;
  std::vector<Vec2> symbols;
  std::vector<Part> parts;

  const char get(int x, int y) const {
    if(y >= lineCount || x >= stride)
      throw std::runtime_error("Puzzle index out of bounds");
    return data[y * stride + x];
  }

  static inline int max(int a, int b) { return a > b  ? a : b; }
  static inline int min(int a, int b) { return a < b  ? a : b; }

  const bool isValidPart(Part& part) {
    // clip the bounding box to the dimensions of the puzzle so
    // we don't attempt to index outside of range
    BoundingBox::clipTo(part.bbox, bbox);

    // int x1 = max(0u, part.start.x - 1u);
    // int x2 = min(stride - 1, part.start.x + part.len);

    // int y1 = max(0u, part.start.y - 1);
    // int y2 = min(lineCount - 1, part.start.y + 1);
    
    // loop through all the surrounding locations looking
    // for a symbol. If one is found, short circuit return true

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

    // for (int y = y1; y <= y2; y++) {
    //   for (int x = x1; x <= x2; x++) {
    //     char c = get(x,y);
    //     if (get(x,y) != '.' && !(c >= '0' && c <= '9')) {
    //       return true;
    //     } 
    //   }
    // }
    return isValid;
  }
};

/// Get the dimensions (x,y) of the data in the file. Will be used
/// to determine the stride
const Puzzle parse(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file " + filename);
  }
  std::string line;
  std::vector<char> contents;  // allocate max expected space
  int width = 0, height = 0;

  bool inNum = false;
  int nStart = 0;
  std::vector<char> numStr;
  std::vector<Part> parts;
  std::vector<Vec2> symbols;

  while (std::getline(file,line)) {
    width = line.length();
    contents.insert(contents.end(), line.begin(), line.end());
    if (inNum) {
      // last line ended in a number, close that one out
      int number = std::stoi(numStr.data());
      int numLen = numStr.size();
      numStr = std::vector<char>();
      Vec2 startLocation{nStart, height - 1};

      BoundingBox bb{Vec2{nStart-1,height - 2}, Vec2{nStart + numLen + 1, height + 1}};
      Part p{startLocation, bb, numLen, number};
      parts.push_back(p);
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
          // we were in a number, wrap it up
          int number = std::stoi(numStr.data());
          int numLen = numStr.size();
          numStr = std::vector<char>();;
          Vec2 startLocation{nStart, height};
          BoundingBox bb{Vec2{nStart - 1,height - 1}, Vec2{nStart + numLen, height + 1}};
          Part p{startLocation, bb, numLen, number };
          parts.push_back(p);
        }
        inNum = false;
        if (cur != '.') {
          symbols.push_back(Vec2{x, height});
        }
      }
    }
    ++height;
  }
  if (inNum) {
      // last line ended in a number, close that one out
      int number = std::stoi(numStr.data());
      int numLen = numStr.size();
      numStr = std::vector<char>();
      Vec2 startLocation{nStart - 1, height - 2};

      BoundingBox bb{Vec2{nStart - 1,height - 2}, Vec2{nStart + numLen + 1, height + 1}};
      Part p{startLocation, bb, numLen, number};
      parts.push_back(p);
      inNum = false;    
  }

  file.close();
  auto bb = BoundingBox{Vec2{0,0}, Vec2{width - 1, height - 1}};
  return Puzzle{contents, width, height, bb, symbols, parts };
}

const uint part1(const std::string& filename) {  // 535235
  Puzzle puz = parse(filename);
  u_int32_t total = 0;
  for (Part& p : puz.parts) {
    if (puz.isValidPart(p)) {
      total += p.num;
    } 
  }
  return total;
}

const uint part2(const std::string& filename) {
  // algo: 
  // scan the file
  // for each symbol
  // scan all the way around the symbol looking for numbers
  // if a number is found, find the whole number and note its starting index
  // de-dupe the found numbers. If the found numbers
  return 0;
}

} // namespace day03
