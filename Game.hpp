#pragma once

#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include "ControlManager.hpp"
#include "ControllableObject.hpp"
#include "GetReadyScreen.hpp"
#include "Interface.hpp"
#include "PipesManager.hpp"
#include "StageManager.hpp"
#include "Text.hpp"

class ActorManager;
class Text;

class Game : public Interface, public ControllableObject {
public:
  explicit Game(Application *const app);

  virtual void draw() const override;
  virtual void update() override;

  enum class GameActions {
    HIDE_GET_READY_SCREEN = 639,
  };

  virtual void doAction(action_t action, int magnitute = 0) override;

  void execute(GameActions action);

  void reinit();
  void over();

  ~Game();

private:
  ControlManager *controlManager;
  ActorManager *actorManager;
  StageManager *stageManager;
  PipesManager *pipesManager;

  Bird *bird;

  Text *textScore;
  GetReadyScreen *getReadyScreen;

  // Game states
  int score;
};

#endif // !GAME_HPP
