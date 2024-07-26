#include <ostream>
#include "vec.hpp"

std::ostream& operator<<(std::ostream& os, const Vec2& vec) {
  os << "(" << vec.x << "," << vec.y << ")";
  return os;
}

BoundingBox BoundingBox::operator+(const Vec2& offset) {
  return {
    {upperLeft.x + offset.x, upperLeft.y + offset.y},
    {lowerRight.x + offset.x, lowerRight.y + offset.y}
  };
}

BoundingBox BoundingBox::operator-(const Vec2& offset) {
  return {
    {upperLeft.x - offset.x, upperLeft.y - offset.y},
    {lowerRight.x - offset.x, lowerRight.y - offset.y}
  };
}

void BoundingBox::clipTo(BoundingBox& boxToClip, BoundingBox& clippingBox) {
  boxToClip.upperLeft.x = std::max(boxToClip.upperLeft.x, clippingBox.upperLeft.x);
  boxToClip.upperLeft.y = std::max(boxToClip.upperLeft.y, clippingBox.upperLeft.y);
  boxToClip.lowerRight.x = std::min(boxToClip.lowerRight.x, clippingBox.lowerRight.x);
  boxToClip.lowerRight.y = std::min(boxToClip.lowerRight.y, clippingBox.lowerRight.y);
}

void BoundingBox::forEachPoint(const std::function<bool(const Vec2&)>& func) const {
  for (int x = upperLeft.x; x <= lowerRight.x; ++x) {
    for (int y = upperLeft.y; y <= lowerRight.y; ++y) {
      if (!func({x, y})) {
        return;
      }
    }
  }
}