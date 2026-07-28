#include <algorithm>

#include "Bird.hpp"
#include "Globals.hpp"
#include "R.hpp"
#include "Sprite.hpp"
#include "Utils.hpp"
#include <raylib.h>

using namespace std;

Bird::Bird(const float &x, const float &y, Game *g) {
  this->game = g;
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
  ticks = 3;
  auto deadIndex = static_cast<size_t>(BirdState::STATE_DEAD);
  this->sprites[deadIndex].setOwner(this);
  this->sprites[deadIndex].setRepeat(false);
  this->sprites[deadIndex].addFrameCentered(R::TextureIds::FLAPPY_SPRITES,
                                            Rectangle{.x = WITH_SCALE(31),
                                                      .y = WITH_SCALE(491),
                                                      .width = birdFrameWidth,
                                                      .height = birdFrameHeight},
                                            ticks);
  ticks = 3;
  auto deadWithFallIndex = static_cast<size_t>(BirdState::DEAD_WITH_FALL);
  this->sprites[deadWithFallIndex].setOwner(this);
  this->sprites[deadWithFallIndex].setRepeat(false);
  this->sprites[deadWithFallIndex].addFrameCentered(R::TextureIds::FLAPPY_SPRITES,
                                                    Rectangle{.x = WITH_SCALE(31),
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
    case BirdState::STATE_MOVING:
    case BirdState::DEAD_WITH_FALL:
      if (activeSprite.getBottom() < Globals::Constants::SURFACE_Y || this->velocity < 0) {
        this->velocity += this->gravity;
        this->position.y += velocity;

        // Jump rotates faster
        this->rotation += (this->velocity > 0 ? this->velocity : this->velocity * 3);

        // TODO: Not sure if this must be the minimum rotation:
        this->rotation = std::max(-30.0f, std::min(90.0f, this->rotation));
      }

      if (activeSprite.getBottom() >= Globals::Constants::SURFACE_Y) { // Die
        this->position.y = Globals::Constants::SURFACE_Y;
        this->setState(BirdState::STATE_DEAD);

      } else if (this->position.y < WITH_SCALE(-70)) { // Avoid going too high. Set a roof.
        this->position.y = WITH_SCALE(-70);
      }
      break;

    case BirdState::STATE_IDLE:
      this->position.y += this->velocity;
      this->velocity += this->gravity;

      if (this->velocity <= -WITH_SCALE(0.5)) {
        this->gravity = WITH_SCALE(0.04);
      }

      if (this->velocity > WITH_SCALE(0.5)) {
        this->gravity = -WITH_SCALE(0.04);
      }

      break;

    default:
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
  if (state == this->state)
    return;

  switch (state) {
    case Bird::BirdState::STATE_IDLE:
      this->velocity = WITH_SCALE(0.5);
      this->gravity = -WITH_SCALE(0.04);
      this->rotation = 0;
      break;

    case Bird::BirdState::STATE_DEAD:
      if (this->state != Bird::BirdState::DEAD_WITH_FALL) {
        PlaySound(R::getSingleton().getSound(R::SoundId::HIT));
        this->game->execute(Game::GameActions::BIRD_DIED);
      }

      break;

    case Bird::BirdState::DEAD_WITH_FALL:
      PlaySound(R::getSingleton().getSound(R::SoundId::HIT));
      PlaySound(R::getSingleton().getSound(R::SoundId::DIE));
      break;

    default:
      break;
  }

  this->state = state;
}

bool Bird::isDead() const {
  return this->state == BirdState::STATE_DEAD || this->state == BirdState::DEAD_WITH_FALL;
}

void Bird::doAction(action_t action, int magnitute) {
  switch (action) {
    case BirdActions::BIRD_ACTION_JUMP:
      if (this->state == BirdState::STATE_DEAD || this->state == BirdState::DEAD_WITH_FALL)
        return;

      if (this->state == BirdState::STATE_IDLE) {
        this->setState(BirdState::STATE_MOVING);
        this->velocity = 0;
        this->gravity = 0.44;
        this->game->execute(Game::GameActions::BIRD_STARTED_MOVING);
      }

      PlaySound(R::getSingleton().getSound(R::SoundId::WING));
      this->velocity = -WITH_SCALE(2.5);

      break;
  }
}

Bird::~Bird() {}
