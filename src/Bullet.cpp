#include "Bullet.hpp"
#include "R.hpp"
#include "Utils.hpp"
#include "raylib.h"

Bullet::Bullet() {

  this->velocity = 350.0f;
  int stateIdleIndex = static_cast<int>(State::IDLE);
  this->sprites[stateIdleIndex].setOwner(this);
  this->sprites[stateIdleIndex].setRepeat(false);
  this->sprites[stateIdleIndex].addFrame(R::TextureIds::FLAPPY_SPRITES,
                                         {
                                             .x = WITH_SCALE(138),
                                             .y = WITH_SCALE(393),
                                             .width = WITH_SCALE(5),
                                             .height = WITH_SCALE(5),
                                         },
                                         3);
};

void Bullet::draw() const {
  this->sprites[static_cast<int>(this->state)].draw();
}

void Bullet::update() {
  this->position.x += GetFrameTime() * this->velocity;
}

float Bullet::getWidth() const {
  return this->sprites[static_cast<int>(this->state)].getWidth();
}

float Bullet::getHeight() const {
  return this->sprites[static_cast<int>(this->state)].getHeight();
}
