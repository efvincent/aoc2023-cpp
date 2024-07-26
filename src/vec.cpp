#include <ostream>
#include "vec.hpp"

std::ostream& operator<<(std::ostream& os, const Vec2& vec) {
  os << "(" << vec.x << "," << vec.y << ")";
  return os;
}

BoundingBox BoundingBox::operator+(const Vec2& offset) const {
  return {
    {upperLeft.x + offset.x, upperLeft.y + offset.y},
    {lowerRight.x + offset.x, lowerRight.y + offset.y}
  };
}

BoundingBox BoundingBox::operator-(const Vec2& offset) const {
  return {
    {upperLeft.x - offset.x, upperLeft.y - offset.y},
    {lowerRight.x - offset.x, lowerRight.y - offset.y}
  };
}

void BoundingBox::clipTo(const BoundingBox& other) {
  upperLeft.x = std::max(upperLeft.x, other.upperLeft.x);
  upperLeft.y = std::max(upperLeft.y, other.upperLeft.y);
  lowerRight.x = std::min(lowerRight.x, other.lowerRight.x);
  lowerRight.y = std::min(lowerRight.y, other.lowerRight.y);
}