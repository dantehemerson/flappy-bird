#include <cstdlib>
#include <ctime>

#include "Utils.hpp"

float Utils::randomFloat(const float &min, const float &max) {
  return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}
