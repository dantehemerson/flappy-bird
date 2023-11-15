#include <algorithm>

#include "Globals.hpp"
#include "Logger.h"
#include "Sprite.hpp"
#include "Surface.hpp"
#include "SurfaceTile.hpp"
#include "Utils.hpp"
#include <raylib.h>

using namespace std;

Surface::Surface(Game *g) {
  // Put one right after the other in X
  this->tiles[0].position = {0, Globals::Constants::SURFACE_Y};
  this->tiles[0].setVelocityX(-WITH_SCALE(1));

  this->tiles[1].position = {WITH_SCALE(168), Globals::Constants::SURFACE_Y};
  this->tiles[1].setVelocityX(-WITH_SCALE(1));

  this->state = Surface::SurfaceState::SURFACE_MOVING;
}

void Surface::draw() const {
  for (auto &tile : this->tiles) {
    tile.draw();
  }
}

void Surface::update() {
  if (this->state == Surface::SurfaceState::SURFACE_MOVING) {
    for (auto &tile : this->tiles) {
      tile.update();
    }
  }
}

void Surface::setVelocityX(const float &velocity) {
  for (auto &tile : this->tiles) {
    tile.setVelocityX(velocity);
  }
}