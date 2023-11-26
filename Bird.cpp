#include <algorithm>

#include "Bird.hpp"
#include "Globals.hpp"
#include "Logger.h"
#include "Sprite.hpp"
#include "Utils.hpp"
#include <raylib.h>

using namespace std;

Bird::Bird(const float &x, const float &y, Game *g) {
  this->position = {x, y};
  this->gravity = 0.44;
  this->velocity = 0;
  this->state = Bird::BirdState::STATE_MOVING;

  this->initializeSprites();
}

void Bird::initializeSprites() {
  // Moving
  float birdFrameWidth = WITH_SCALE(17);
  float birdFrameHeight = WITH_SCALE(12);
  int ticks = 3;

  auto movingIndex = static_cast<size_t>(Bird::BirdState::STATE_MOVING);
  this->sprites[movingIndex].setOwner(this);
  this->sprites[movingIndex].setRepeat(true);
  this->sprites[movingIndex].addFrameCentered(R::TextureIds::FLAPPY_SPRITES,
                                              {.x = WITH_SCALE(3),
                                               .y = WITH_SCALE(491),
                                               .width = birdFrameWidth,
                                               .height = birdFrameHeight},
                                              ticks);
  this->sprites[movingIndex].addFrameCentered(R::TextureIds::FLAPPY_SPRITES,
                                              Rectangle{.x = WITH_SCALE(31),
                                                        .y = WITH_SCALE(491),
                                                        .width = birdFrameWidth,
                                                        .height = birdFrameHeight},
                                              ticks);
  this->sprites[movingIndex].addFrameCentered(R::TextureIds::FLAPPY_SPRITES,
                                              Rectangle{.x = WITH_SCALE(59),
                                                        .y = WITH_SCALE(491),
                                                        .width = birdFrameWidth,
                                                        .height = birdFrameHeight},
                                              ticks);

  ticks = 7;
  auto idleIndex = static_cast<size_t>(Bird::BirdState::STATE_IDLE);
  this->sprites[idleIndex].setOwner(this);
  this->sprites[idleIndex].setRepeat(true);
  this->sprites[idleIndex].addFrameCentered(R::TextureIds::FLAPPY_SPRITES,
                                            {.x = WITH_SCALE(3),
                                             .y = WITH_SCALE(491),
                                             .width = birdFrameWidth,
                                             .height = birdFrameHeight},
                                            ticks);
  this->sprites[idleIndex].addFrameCentered(R::TextureIds::FLAPPY_SPRITES,
                                            Rectangle{.x = WITH_SCALE(31),
                                                      .y = WITH_SCALE(491),
                                                      .width = birdFrameWidth,
                                                      .height = birdFrameHeight},
                                            ticks);
  this->sprites[idleIndex].addFrameCentered(R::TextureIds::FLAPPY_SPRITES,
                                            Rectangle{.x = WITH_SCALE(59),
                                                      .y = WITH_SCALE(491),
                                                      .width = birdFrameWidth,
                                                      .height = birdFrameHeight},
                                            ticks);
}

void Bird::draw() const {
  this->sprites[static_cast<size_t>(this->state)].draw();
}

void Bird::update() {
  Sprite &activeSprite = this->sprites[static_cast<size_t>(this->state)];

  switch (this->state) {
    case Bird::BirdState::STATE_MOVING:
      if (activeSprite.getBottom() < Globals::Constants::SURFACE_Y || this->velocity < 0) {
        this->velocity += this->gravity;
        this->position.y += velocity;

        // Jump rotates faster
        this->rotation += (this->velocity > 0 ? this->velocity : this->velocity * 3);

        // TODO: Not sure if this must be the minimum rotation:
        this->rotation = std::max(-30.0f, std::min(90.0f, this->rotation));
      }

      if (activeSprite.getBottom() >= Globals::Constants::SURFACE_Y) {
        this->position.y =
            Globals::Constants::SURFACE_Y - activeSprite.getHeight() / 2 + WITH_SCALE(2);
        // TODO: Die here
      } else if (this->position.y < WITH_SCALE(-70)) { // Avoid going too high
        this->position.y = WITH_SCALE(-70);
      }
      break;
    case Bird::BirdState::STATE_IDLE:
      this->position.y += this->velocity;
      this->velocity += this->gravity;

      if (this->velocity <= -WITH_SCALE(0.5)) {
        this->gravity = WITH_SCALE(0.04);
      }

      if (this->velocity > WITH_SCALE(0.5)) {
        this->gravity = -WITH_SCALE(0.04);
      }

      break;
  }

  activeSprite.update();
}

EllipseRotated Bird::getEllipsis() const {
  static const float paddingWidth = WITH_SCALE(0.5f);
  static const float paddingHeight = WITH_SCALE(0.5f);

  return {this->position.x + paddingWidth - WITH_SCALE(0.5f) -
              this->sprites[static_cast<size_t>(this->state)].getWidth() / 2,
          this->position.y + paddingHeight - WITH_SCALE(0.5f) -
              this->sprites[static_cast<size_t>(this->state)].getHeight() / 2,
          this->sprites[static_cast<size_t>(this->state)].getWidth() / 2 - paddingWidth -
              WITH_SCALE(1.0f),
          this->sprites[static_cast<size_t>(this->state)].getHeight() / 2 - paddingHeight +
              WITH_SCALE(0.5f),
          this->rotation};
}

void Bird::setState(BirdState state) {
  switch (state) {
    case Bird::BirdState::STATE_IDLE:
      this->velocity = WITH_SCALE(0.5);
      this->gravity = -WITH_SCALE(0.04);
      this->rotation = 0;
      break;
  }

  this->state = state;
}

void Bird::doAction(action_t action, int magnitute) {
  switch (action) {
    case BirdActions::BIRD_ACTION_JUMP:
      PlaySound(R::getSingleton().getSound(R::SoundId::WING));
      this->velocity = -WITH_SCALE(2.5);
      break;
  }
}

Bird::~Bird() {}
