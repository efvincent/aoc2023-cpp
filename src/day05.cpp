#include "day05.hpp"
#include "util.hpp"
#include <array>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace Day05 {

  /*----------------------------- Types -----------------------------*/

  struct Range {
    ulInt start{0};
    ulInt end{0};
    int len{0};
    bool contains(ulInt value) const { return value >= start && value <= end; }
    static Range mk_by_end(const ulInt start, const ulInt end) {
      ulInt s, e;
      if (end < start) {
        s = end;
        e = start;
      } else {
        s = start;
        e = end;
      }
      return Range{s, e, static_cast<int>(e - s) };
    }
    static Range mk_by_len(const ulInt start, const int len) {
      return Range{start, start + len - 1, len };
    }
  };

  struct RangeMap {
    Range dest;
    Range source;
    bool in_source(ulInt value) const { return source.contains(value); }
  };

  using RangeMaps = std::vector<RangeMap>;

  struct Puzzle {
    std::vector<ulInt> seeds;
    std::vector<Range> seed_ranges;
    std::array<RangeMaps, 7> range_maps;
  };

  using ulInts = std::vector<ulInt>;
  using str_views = std::vector<std::string_view>;

  /*------------------------ Puzzle Printing ------------------------*/

  // Overload the << operator for the Range struct
  std::ostream& operator<<(std::ostream& os, const Range& range) {
      os << range.start << "->" << range.end;
      return os;
  }

  // Overload the << operator for the Range struct
  std::ostream& operator<<(std::ostream& os, const RangeMap& range_map) {
      os << range_map.source << " maps to " << range_map.dest;
      return os;
  }
  
  void pRangeMaps(const int rm_num, const RangeMaps& rm) {
    std::cout << "range map " << rm_num << ":" << "\n";
    for (const RangeMap& r : rm) {
      std::cout << "  " << r << "\n";
    }
    std::cout << "\n";
  }

  void pPuzzle(const Puzzle& puz) {
    std::cout << "seeds:";
    for (const auto& seed : puz.seeds) {
      std::cout << " " << seed;
    }
    
    std::cout << "\nseed ranges:";
    for (const auto& seed_range : puz.seed_ranges) {
      std::cout << "\n  " << seed_range;
    }

    std::cout << "\n\n";
    for (int i = 0; i < puz.range_maps.size(); i++) {
      pRangeMaps(i, puz.range_maps[i]);
    }
  }  
  
  /*----------------------------- Parsing -----------------------------*/

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
    for (int i = 0; i < puz.seeds.size() - 1; i += 2) {
      puz.seed_ranges.push_back(Range::mk_by_end(puz.seeds[i], puz.seeds[i+1]));
    }
    
    for (int split_idx = 1; split_idx < split1.size(); split_idx++) {
      str_views raw_range_map = Util::splitOn(split1[split_idx], "\n");
      RangeMaps range_maps;
      for (int range_map_idx = 1; range_map_idx < raw_range_map.size(); range_map_idx++) {
        str_views raw_line = Util::splitOn(raw_range_map[range_map_idx], " ");
        int len = std::stoi(raw_line[2].data());
        Range dest = Range::mk_by_len(std::stoul(raw_line[0].data()), len);
        Range src  = Range::mk_by_len(std::stoul(raw_line[1].data()), len);
        RangeMap range_map { dest, src };
        range_maps.push_back(range_map);
      }
      puz.range_maps[split_idx-1] = range_maps;
    }
    return puz;
  }

  /*----------------------------- Solutions ----------------------------*/

  ulInt deref_step(const Puzzle& puz, int mapIdx, ulInt value) {
    // get the range map we need
    RangeMaps rm = puz.range_maps[mapIdx];
    // test the ranges to see if the value is mapped
    for(const auto& range : rm) {
      if (range.in_source(value)) {
        // value is in this range, map it
        ulInt offset = value - range.source.start;
        ulInt mapped_value = range.dest.start + offset;
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
    pPuzzle(puz);

    return std::pair(*std::min_element(mapped_seeds.begin(), mapped_seeds.end()), 0);
  }
}