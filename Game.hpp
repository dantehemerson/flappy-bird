#pragma once

#ifndef GAME_HPP
#define GAME_HPP

#include "ControlManager.hpp"
#include "ControllableObject.hpp"
#include "FinishScreen.hpp"
#include "GetReadyScreen.hpp"
#include "Interface.hpp"
#include "PipesManager.hpp"
#include "StageManager.hpp"
#include "Text.hpp"

class ActorManager;
class Text;
class FinishScreen;
class Surface;

class Game : public Interface, public ControllableObject {
public:
  explicit Game(Application *const app);

  enum class GameState : size_t { GET_READY = 1, PLAYING, FINISH };

  virtual void draw() const override;
  virtual void update() override;

  enum class GameActions {
    BIRD_STARTED_MOVING = 639,
    BIRD_DIED,
    PLAY_AGAIN
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
  Surface* surface;

  Bird *bird;

  Text *textScore;
  GetReadyScreen *getReadyScreen;
  FinishScreen *finishScreen;

  // Game states
  int score;
};

#endif // !GAME_HPP
