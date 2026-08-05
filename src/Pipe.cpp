#include <algorithm>

#include "Bullet.hpp"
#include "Globals.hpp"
#include "Pipe.hpp"
#include "Utils.hpp"
#include <raylib.h>
#include <rlgl.h>

using namespace std;

Pipe::Pipe() {
  this->_hasPassedBird = false;
  this->initializeSprites();
  this->reset();
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
      .setDisplacementY(this->spritePipeTop.getHeight() + Globals::Constants::PIPES_VERTICAL_GAP);
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

bool Pipe::hasCollided(const Bird *bird) const {
  // Add -200 to check collition when bird is too high
  Rectangle pipeTop{this->position.x + WITH_SCALE(1), this->position.y - WITH_SCALE(200),
                    this->spritePipeTop.getWidth(),
                    this->spritePipeTop.getHeight() + WITH_SCALE(200)};
  Rectangle pipeBottom = {this->position.x + WITH_SCALE(1),
                          this->position.y + this->spritePipeTop.getHeight() +
                              Globals::Constants::PIPES_VERTICAL_GAP,
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
    return true;
  }

  // #if BUILD_MODE == DEBUG
  //   DrawLineV(closestPointTop, {birdEllipse.x, birdEllipse.y}, RED);
  //   DrawLineV(closestPointBottom, {birdEllipse.x, birdEllipse.y}, RED);

  //   rlPushMatrix();
  //   rlTranslatef(birdEllipse.x, birdEllipse.y, 0);
  //   rlRotatef(birdEllipse.rotation, 0, 0, 1);
  //   DrawEllipseLines(0, 0, birdEllipse.width, birdEllipse.height, RED);
  //   rlPopMatrix();

  //   DrawRectangleLinesEx(pipeTop, 1, RED);
  //   DrawRectangleLinesEx(pipeBottom, 1, RED);
  // #endif

  return false;
}

bool Pipe::hasCollided(const Bullet *bullet) const {
  Rectangle bulletRect{bullet->position.x, bullet->position.y, bullet->getWidth(),
                       bullet->getHeight()};

  // Add -200 to check collition when bullet is too high
  Rectangle pipeTop{this->position.x + WITH_SCALE(1), this->position.y - WITH_SCALE(200),
                    this->spritePipeTop.getWidth(),
                    this->spritePipeTop.getHeight() + WITH_SCALE(200)};
  Rectangle pipeBottom = {this->position.x + WITH_SCALE(1),
                          this->position.y + this->spritePipeTop.getHeight() +
                              Globals::Constants::PIPES_VERTICAL_GAP,
                          this->spritePipeBottom.getWidth(), this->spritePipeBottom.getHeight()};

  return CheckCollisionRecs(bulletRect, pipeTop) || CheckCollisionRecs(bulletRect, pipeBottom);
}

bool Pipe::isAlive() const {
  return this->lives >= 1;
}

void Pipe::reset() {
  this->lives = 10;
}
