#include <algorithm>

#include "Logger.h"
#include "Pipe.hpp"
#include "Utils.hpp"
#include <raylib.h>

using namespace std;

Pipe::Pipe() {
  this->_hasPassedBird = false;
  this->initializeSprites();
}

void Pipe::initializeSprites() {
  this->spritePipeTop.setOwner(this);
  this->spritePipeTop.setRepeat(true);
  this->spritePipeTop.addFrame(R::TextureIds::FLAPPY_SPRITES,
                               {.x = WITH_SCALE(56),
                                .y = WITH_SCALE(323),
                                .width = WITH_SCALE(26),
                                .height = WITH_SCALE(160)},
                               60);

  this->spritePipeBottom.setOwner(this);
  this->spritePipeBottom.setRepeat(true);
  this->spritePipeBottom
      .addFrame(R::TextureIds::FLAPPY_SPRITES,
                {.x = WITH_SCALE(84),
                 .y = WITH_SCALE(323),
                 .width = WITH_SCALE(26),
                 .height = WITH_SCALE(160)},
                60)
      .setDisplacementY(this->spritePipeTop.getHeight() + WITH_SCALE(42));
}

void Pipe::draw() const {
  this->spritePipeTop.draw();
  this->spritePipeBottom.draw();
}

void Pipe::update() {}

float Pipe::getWidth() const {
  return WITH_SCALE(26);
}

void Pipe::setHasPassedBird(const bool &hasPassedBird) {
  this->_hasPassedBird = hasPassedBird;
}

bool Pipe::hasPassedBird() const {
  return this->_hasPassedBird;
}

bool Pipe::hasCollided(Bird *bird) {
  Rectangle pipeTop{this->position.x + WITH_SCALE(1), this->position.y - WITH_SCALE(200),
                    this->spritePipeTop.getWidth(),
                    this->spritePipeTop.getHeight() + WITH_SCALE(200)};
  Rectangle pipeBottom = {this->position.x + WITH_SCALE(1),
                          this->position.y + this->spritePipeTop.getHeight() + WITH_SCALE(42),
                          this->spritePipeBottom.getWidth(), this->spritePipeBottom.getHeight()};

  EllipseRotated birdEllipse = bird->getEllipsis();

  Vector2 closestPointTop = {
      std::clamp(birdEllipse.x, pipeTop.x, pipeTop.x + pipeTop.width),
      std::clamp(birdEllipse.y, pipeTop.y, pipeTop.y + pipeTop.height),
  };

  Vector2 closestPointBottom = {
      std::clamp(birdEllipse.x, pipeBottom.x, pipeBottom.x + pipeBottom.width),
      std::clamp(birdEllipse.y, pipeBottom.y, pipeBottom.y + pipeBottom.height),
  };

  if (Utils::isCollisionVectorEllipseRotated(closestPointTop, birdEllipse) ||
      Utils::isCollisionVectorEllipseRotated(closestPointBottom, birdEllipse)) {
#if BUILD_MODE == DEBUG
    LogInfo << "Collision: true" << endl;
#endif
    // return true;
  } else {
#if BUILD_MODE == DEBUG
    LogInfo << "Collision: ___" << endl;
#endif
  }

#if BUILD_MODE == DEBUG
  DrawLineV(closestPointTop, {birdEllipse.x, birdEllipse.y}, RED);
  DrawLineV(closestPointBottom, {birdEllipse.x, birdEllipse.y}, RED);

  DrawEllipseLines(birdEllipse.x, birdEllipse.y, birdEllipse.width, birdEllipse.height, WHITE);
  // Add 100px to check collition when bird is too high
  DrawRectangleLinesEx(pipeTop, 1, RED);

  DrawRectangleLinesEx(pipeBottom, 1, RED);
#endif

  return false;
}
