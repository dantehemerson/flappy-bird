#include <cmath>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <raylib.h>
#include <unordered_map>

#include "Utils.hpp"

using namespace std;

float Utils::randomFloat(const float &min, const float &max) {
  return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

bool Utils::isCollisionVectorEllipseRotated(const Vector2 &point, const EllipseRotated &ellipse) {
  // Rotate the point back to the ellipse's local coordinate system
  float rotatedX = std::cos(-ellipse.rotation * M_PI / 180.0f) * (point.x - ellipse.x) -
                   std::sin(-ellipse.rotation * M_PI / 180.0f) * (point.y - ellipse.y);
  float rotatedY = std::sin(-ellipse.rotation * M_PI / 180.0f) * (point.x - ellipse.x) +
                   std::cos(-ellipse.rotation * M_PI / 180.0f) * (point.y - ellipse.y);

  // Calculate the normalized distance between the rotated point and the ellipse
  float normalizedX = rotatedX / ellipse.width;
  float normalizedY = rotatedY / ellipse.height;

  // Check if the normalized distance is within the ellipse
  return (normalizedX * normalizedX + normalizedY * normalizedY) <= 1.0f;
}

std::unordered_map<Utils::FONT_SIZE, std::unordered_map<char, Rectangle>> Utils::fontSources = {
    {Utils::FONT_SIZE::SMALL,
     {
         {'0', {WITH_SCALE(137), WITH_SCALE(306), WITH_SCALE(7), WITH_SCALE(10)}},
         {'1', {WITH_SCALE(137), WITH_SCALE(477), WITH_SCALE(7), WITH_SCALE(10)}},
         {'2', {WITH_SCALE(137), WITH_SCALE(489), WITH_SCALE(7), WITH_SCALE(10)}},
         {'3', {WITH_SCALE(131), WITH_SCALE(501), WITH_SCALE(7), WITH_SCALE(10)}},
         {'4', {WITH_SCALE(502), WITH_SCALE(0), WITH_SCALE(7), WITH_SCALE(10)}},
         {'5', {WITH_SCALE(502), WITH_SCALE(12), WITH_SCALE(7), WITH_SCALE(10)}},
         {'6', {WITH_SCALE(505), WITH_SCALE(26), WITH_SCALE(7), WITH_SCALE(10)}},
         {'7', {WITH_SCALE(505), WITH_SCALE(42), WITH_SCALE(7), WITH_SCALE(10)}},
         {'8', {WITH_SCALE(293), WITH_SCALE(242), WITH_SCALE(7), WITH_SCALE(10)}},
         {'9', {WITH_SCALE(311), WITH_SCALE(206), WITH_SCALE(7), WITH_SCALE(10)}},
     }},

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
