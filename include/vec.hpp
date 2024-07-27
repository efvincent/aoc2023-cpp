#pragma once
#include <functional>

struct Vec2 {
  int x;
  int y;

  // Parameterized constructor
  Vec2(int x, int y) : x(x), y(y) {}

  // Move constructor
  Vec2(Vec2&& other) noexcept : x(other.x), y(other.y) {
    other.x = 0;
    other.y = 0;
  }

  // Move assignment operator
  Vec2& operator=(Vec2&& other) noexcept {
    if (this != &other) {
      x = other.x;
      y = other.y;
      other.x = 0;
      other.y = 0;
    }
    return *this;
  }

  // Copy constructor
  Vec2(const Vec2& other) = default;

  // Copy assignment operator
  Vec2& operator=(const Vec2& other) = default;
};

struct BoundingBox {
  BoundingBox() = delete;

  // Move constructor
  BoundingBox(Vec2&& upperLeft, Vec2&& lowerRight) : 
    upperLeft(std::move(upperLeft)), 
    lowerRight(std::move(lowerRight)) {}

  // Move constructor 
  BoundingBox(BoundingBox&& other) : 
    upperLeft(std::move(other.upperLeft)),
    lowerRight(std::move(other.lowerRight)) {}
  
  // Delete copy constructor and copy assignment operator
  // copying is not allowed
  BoundingBox(const BoundingBox&) = delete;
  BoundingBox& operator=(const BoundingBox&) = delete;

  // Move assignment operator
  BoundingBox& operator=(BoundingBox&& other) noexcept {
    if (this != &other) {
      upperLeft = std::move(other.upperLeft);
      lowerRight = std::move(other.lowerRight);
    }
    return *this;
  }

  Vec2 upperLeft;
  Vec2 lowerRight;

  BoundingBox operator+(const Vec2& offset);
  BoundingBox operator-(const Vec2& offset);
  static void clipTo(BoundingBox& boxToClip, const BoundingBox& clippingBox);
  void forEachPoint(const std::function<bool(const Vec2&)>& func) const;
  bool isPointInBox(const Vec2& point) const;
};