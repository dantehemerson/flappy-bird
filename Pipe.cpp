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
  // Add 100px to check collition when bird is too high
  DrawRectangleLinesEx({this->position.x + WITH_SCALE(1), this->position.y - WITH_SCALE(200),
                        this->spritePipeTop.getWidth(),
                        this->spritePipeTop.getHeight() + WITH_SCALE(200)},
                       1, RED);

  DrawRectangleLinesEx({this->position.x + WITH_SCALE(1),
                        this->position.y + this->spritePipeTop.getHeight() + WITH_SCALE(42),
                        this->spritePipeBottom.getWidth(), this->spritePipeBottom.getHeight()},
                       1, RED);
}
