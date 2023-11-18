#include <cstdlib>
#include <ctime>

#include <map>

#include "Utils.hpp"

using namespace std;

float Utils::randomFloat(const float &min, const float &max) {
  return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

std::unordered_map<Utils::FONT_SIZE, std::unordered_map<char, Rectangle>> Utils::fontSources = {

    {Utils::FONT_SIZE::LARGE,
     {
         {'0', {WITH_SCALE(496), WITH_SCALE(60), WITH_SCALE(12), WITH_SCALE(18)}},
         {'1', {WITH_SCALE(132), WITH_SCALE(455), WITH_SCALE(12), WITH_SCALE(18)}},
         {'2', {WITH_SCALE(292), WITH_SCALE(160), WITH_SCALE(12), WITH_SCALE(18)}},
         {'3', {WITH_SCALE(306), WITH_SCALE(160), WITH_SCALE(12), WITH_SCALE(18)}},
         {'4', {WITH_SCALE(320), WITH_SCALE(160), WITH_SCALE(12), WITH_SCALE(18)}},
         {'5', {WITH_SCALE(334), WITH_SCALE(160), WITH_SCALE(12), WITH_SCALE(18)}},
         {'6', {WITH_SCALE(292), WITH_SCALE(184), WITH_SCALE(12), WITH_SCALE(18)}},
         {'7', {WITH_SCALE(306), WITH_SCALE(184), WITH_SCALE(12), WITH_SCALE(18)}},
         {'8', {WITH_SCALE(320), WITH_SCALE(184), WITH_SCALE(12), WITH_SCALE(18)}},
         {'9', {WITH_SCALE(334), WITH_SCALE(184), WITH_SCALE(12), WITH_SCALE(18)}},
     }},

};
