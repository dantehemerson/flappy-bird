#pragma once

#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include "ControlManager.hpp"
#include "ControllableObject.hpp"
#include "Interface.hpp"
#include "StageManager.hpp"

class ActorManager;

class Game : public Interface, public ControllableObject {
public:
  explicit Game(Application *const app);

  virtual void draw() const override;
  virtual void update() override;
  virtual void doAction(action_t action, int magnitute) override;

  void reinit();
  void over();

  ~Game();

private:
  ControlManager *controlManager;
  ActorManager *actorManager;
  StageManager *stageManager;

  // Game states
  int score;
};

#endif // !GAME_HPP
