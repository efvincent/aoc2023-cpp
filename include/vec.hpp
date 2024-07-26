#pragma once

struct Vec2 {
  int x;
  int y;
};

struct BoundingBox {
  Vec2 upperLeft;
  Vec2 lowerRight;

  BoundingBox operator+(const Vec2& offset) const;
  BoundingBox operator-(const Vec2& offset) const;
  void clipTo(const BoundingBox& other);
};