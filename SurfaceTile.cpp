#include <algorithm>

#include "Logger.h"
#include "Sprite.hpp"
#include "SurfaceTile.hpp"
#include "Utils.hpp"
#include <raylib.h>

using namespace std;

SurfaceTile::SurfaceTile() {
  this->position = {0, 0};
  this->velocityX = 0;

  this->initializeSprites();
}

void SurfaceTile::initializeSprites() {
  sprite.setOwner(this);
  sprite.setRepeat(true);
  sprite.addFrame(
      R::TextureIds::FLAPPY_SPRITES,
      {.x = WITH_SCALE(292), .y = 0, .width = WITH_SCALE(168), .height = WITH_SCALE(56)}, 60);
}

void SurfaceTile::draw() const {
  this->sprite.draw();
}

void SurfaceTile::update() {
  this->position.x += this->velocityX;

  if (this->position.x <= -WITH_SCALE(168)) {
    this->position.x = this->position.x + WITH_SCALE(168) * 2;
  }

  LogInfo << this->position.x << " " << this->position.y << endl;
}
