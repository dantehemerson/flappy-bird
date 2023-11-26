#ifndef FINISH_SCREEN_HPP
#define FINISH_SCREEN_HPP

#include "Actor.hpp"
#include "Game.hpp"

class Game;

class FinishScreen : public Actor {
public:
  FinishScreen(Game *g);

  virtual void draw() const override;
  virtual void update() override;

  enum class State { SHOW = 1, SHOWING, HIDDING, HIDDEN };

  void setState(State state);

private:
  Game *game;
  State state;
  float opacity;
};

#endif // !FINISH_SCREEN_HPP
