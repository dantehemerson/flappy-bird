#include <algorithm>

#include "Bird.hpp"
#include "Logger.h"
#include "Sprite.hpp"
#include "Utils.hpp"
#include <raylib.h>

using namespace std;

Bird::Bird(const float &x, const float &y, Game *g) {
  this->position = {x, y};
  this->gravity = 0.4;
  this->velocity = 0;
  this->state = Bird::BirdState::STATE_MOVING;

  this->initializeSprites();
}

void Bird::initializeSprites() {
  // Moving
  float birdFrameWidth = WITH_SCALE(17);
  int ticks = 3;
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
  LogInfo << this->position.x << " " << this->position.y << "      g: " << this->gravity
          << "       v: " << this->velocity << endl;

  Sprite &activeSprite = this->sprites[static_cast<size_t>(this->state)];

  if (this->position.y - activeSprite.getHeight() < 800 || this->velocity < 0) {
    this->velocity += this->gravity;
    this->position.y += velocity;

    // Jump rotates faster
    this->rotation += (this->velocity > 0 ? this->velocity : this->velocity * 3);

    // TODO: Not sure if this must be the minimum rotation:
    this->rotation = std::max(-30.0f, std::min(90.0f, this->rotation));
  }

  activeSprite.update();
}

void Bird::doAction(action_t action, int magnitute) {
  switch (action) {
    case BirdActions::BIRD_ACTION_JUMP:
      this->velocity = -WITH_SCALE(2.5);
      break;
  }
}