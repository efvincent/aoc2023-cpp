#pragma once
#include <functional>

struct Vec2 {
  int x;
  int y;
};

struct BoundingBox {
  Vec2 upperLeft;
  Vec2 lowerRight;

  BoundingBox operator+(const Vec2& offset);
  BoundingBox operator-(const Vec2& offset);
  static void clipTo(BoundingBox& boxToClip, BoundingBox& clippingBox);
  void forEachPoint(const std::function<bool(const Vec2&)>& func) const;
};