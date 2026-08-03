#pragma once
#include <memory>
#include <vector>
#ifndef BIRD_HPP
#define BIRD_HPP

#include <array>

#include "ControllableActor.hpp"
#include "Game.hpp"
#include "Sprite.hpp"
#include "Utils.hpp"

class Game;

enum BirdActions { BIRD_ACTION_JUMP = 1, SHOOT };

class Bird : public ControllableActor {
public:
  Bird(const float &x, const float &y, Game *g);

  enum class BirdState { STATE_IDLE = 1, STATE_MOVING, STATE_DEAD, DEAD_WITH_FALL };

  virtual void draw() const override;
  virtual void update() override;
  virtual void doAction(action_t action, int magnitute) override;

  void setState(BirdState state);

  bool isDead() const;

  EllipseRotated getEllipsis() const;

  ~Bird();

private:
  void initializeSprites();

  Game *game;
  BirdState state;
  std::array<Sprite, 13> sprites;
  std::vector<Actor *> bullets;
  float lastShootTime = 0.0f;
  float shootCooldown;

  float velocity;
  float gravity;
};

#endif // !BIRD_HPP
