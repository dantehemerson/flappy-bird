#pragma once
#ifndef UTILS_HPP
#define UTILS_HPP

#include <raylib.h>

using namespace std;

#define WITH_SCALE(value) (value * 4)

namespace Utils {
  float randomFloat(const float &min, const float &max);

  enum FONT_SIZE { LARGE = 64 };

  extern unordered_map<FONT_SIZE, unordered_map<char, Rectangle>> fontSources;
} // namespace Utils

#endif // !UTILS_HPP
