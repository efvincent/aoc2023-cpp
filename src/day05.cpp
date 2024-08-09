#include "day05.hpp"
#include "util.hpp"
#include <array>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace Day05 {

  struct Range {
    ulInt dest_start{0};
    ulInt source_start{0};
    int len{0};
  };

  void pRange(const Range& range) {
    std::cout << range.source_start << "->" << range.source_start + range.len - 1
      << " maps to " << range.dest_start << "->" << range.dest_start + range.len - 1 
      << "\n";
  }

  using RangeMap = std::vector<Range>;
  
  void pRangeMap(const int rm_num, const RangeMap& rm) {
    std::cout << "range map " << rm_num << ":" << "\n";
    for (const Range& r : rm) {
      std::cout << "  ";
      pRange(r);      
    }
    std::cout << "\n";
  }

  struct Puzzle {
    std::vector<ulInt> seeds;
    std::array<RangeMap, 7> range_maps;
  };

  void pPuzzle(const Puzzle& puz) {
    std::cout << "seeds:";
    for (const auto& seed : puz.seeds) {
      std::cout << " " << seed;
    }
    std::cout << "\n\n";
    for (int i = 0; i < puz.range_maps.size(); i++) {
      pRangeMap(i, puz.range_maps[i]);
    }
  }

  using ulInts = std::vector<ulInt>;
  using str_views = std::vector<std::string_view>;

  Puzzle parse(std::string filename) {
    std::ifstream file{filename};
    if (!file.is_open()) {
      throw new std::runtime_error("Could not open file");
    }
    Puzzle puz;
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string raw = buffer.str();

    str_views split1 = Util::splitOn(raw, "\n\n");
    str_views seedsRaw = Util::splitOn(Util::splitOn(split1[0], ":")[1], " ");

    for (const auto& seedRaw : seedsRaw) {
      puz.seeds.push_back(std::stoul(seedRaw.data()));
    }
    
    for (int i = 1; i < split1.size(); i++) {
      str_views rawMap = Util::splitOn(split1[i], "\n");
      RangeMap rmap;
      for (int j = 1; j < rawMap.size(); j++) {
        str_views rawMapLine = Util::splitOn(rawMap[j], " ");
        Range r {
          std::stoul(rawMapLine[0].data()),
          std::stoul(rawMapLine[1].data()),
          std::stoi(rawMapLine[2].data())
        };
        rmap.push_back(r);
      }
      puz.range_maps[i-1] = rmap;
    }
    return puz;
  }

  ulInt deref_step(const Puzzle& puz, int mapIdx, ulInt value) {
    // get the range map we need
    RangeMap rm = puz.range_maps[mapIdx];
    // test the ranges to see if the value is mapped
    for(const auto& range : rm) {
      if (value >= range.source_start && value <= range.source_start + range.len - 1) {
        // value is in this range, map it
        ulInt offset = value - range.source_start;
        ulInt mapped_value = range.dest_start + offset;
        return mapped_value;
      }
    }
    return value;
  }

  ulInt deref_seed(const Puzzle& puz, const ulInt seed) {    
    ulInt mapped{seed};
    for (int i = 0; i < puz.range_maps.size(); i++) {
      mapped = deref_step(puz, i, mapped);
    }
    return mapped;
  }

  std::pair<ulInt,ulInt> solve(std::string filename) {
    Puzzle puz = parse(filename);
    std::vector<ulInt> mapped_seeds;
    for(const ulInt seed : puz.seeds) {
      ulInt mapped = deref_seed(puz, seed);
      mapped_seeds.push_back(mapped);
    }

    return std::pair(*std::min_element(mapped_seeds.begin(), mapped_seeds.end()), 0);
  }
}