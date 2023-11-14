#include "Bird.hpp"
#include "Logger.h"
#include "Sprite.hpp"
#include "Utils.hpp"
#include <raylib.h>

using namespace std;

Bird::Bird(const float &x, const float &y, Game *g) {
  this->position = {x, y};
  this->velocity = 6;
  this->state = Bird::BirdState::STATE_MOVING;

  this->initializeSprites();
}

void Bird::initializeSprites() {
  // Moving
  float birdFrameWidth = WITH_SCALE(17);
  int ticks = 5;
  auto movingIndex = static_cast<size_t>(Bird::BirdState::STATE_MOVING);
  this->sprites[movingIndex].setOwner(this);
  this->sprites[movingIndex].setRepeat(true);
  this->sprites[movingIndex].addFrame(R::TextureIds::FLAPPY_SPRITES,
                                      {.x = WITH_SCALE(3),
                                       .y = WITH_SCALE(491),
                                       .width = birdFrameWidth,
                                       .height = birdFrameWidth},
                                      ticks);
  this->sprites[movingIndex].addFrame(R::TextureIds::FLAPPY_SPRITES,
                                      Rectangle{.x = WITH_SCALE(31),
                                                .y = WITH_SCALE(491),
                                                .width = birdFrameWidth,
                                                .height = birdFrameWidth},
                                      ticks);
  this->sprites[movingIndex].addFrame(R::TextureIds::FLAPPY_SPRITES,
                                      Rectangle{.x = WITH_SCALE(59),
                                                .y = WITH_SCALE(491),
                                                .width = birdFrameWidth,
                                                .height = birdFrameWidth},
                                      ticks);
}

void Bird::draw() const {
  this->sprites[static_cast<size_t>(this->state)].draw();
}

void Bird::update() {
  LogInfo << this->position.x << " " << this->position.y << endl;

  Sprite &activeSprite = this->sprites[static_cast<size_t>(this->state)];

  if (this->position.y - activeSprite.getHeight() < 800) {
    this->position.y += velocity;
  }

  activeSprite.update();
}

void Bird::doAction(action_t action, int magnitute) {
  switch (action) {
    case BirdActions::BIRD_ACTION_RIGHT:
      this->position.x = this->position.x + this->velocity;
      break;

    case BirdActions::BIRD_ACTION_LEFT:
      this->position.x = this->position.x - this->velocity;
      break;

    case BirdActions::BIRD_ACTION_UP:
      this->position.y = this->position.y - this->velocity * 8;
      break;

    case BirdActions::BIRD_ACTION_DOWN:
      this->position.y = this->position.y + this->velocity;
      break;
  }
}