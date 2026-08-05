#pragma once

#include "Actor.hpp"
#include "Sprite.hpp"
#include <array>

class Bullet : public Actor {
public:
  Bullet();

  enum class State { IDLE = 0 };

  virtual void draw() const override;
  virtual void update() override;

  void setHasPassedBird(const bool &hasPassedBird);

  float getWidth() const;
  float getHeight() const;
  bool hasPassedBird() const;
  bool hasCollided(Actor *bird);

private:
  void initializeSprites();
  bool _hasPassedBird;
  State state = State::IDLE;
  float velocity;
  array<Sprite, 1> sprites;
};
