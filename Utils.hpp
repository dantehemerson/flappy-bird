#pragma once
#ifndef UTILS_HPP
#define UTILS_HPP

#include <unordered_map>
#include <raylib.h>

using namespace std;

#define WITH_SCALE(value) (value * 4)

struct EllipseRotated : public Rectangle {
  float rotation;
};

namespace Utils {
  float randomFloat(const float &min, const float &max);
  bool isCollisionVectorEllipseRotated(const Vector2 &point, const EllipseRotated &ellipse);

  enum FONT_SIZE { SMALL = 12, LARGE = 64 };

  extern std::unordered_map<FONT_SIZE, unordered_map<char, Rectangle>> fontSources;
} // namespace Utils

#endif // !UTILS_HPP
