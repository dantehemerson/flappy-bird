#ifndef FINISH_SCREEN_HPP
#define FINISH_SCREEN_HPP

#include "Actor.hpp"
#include "Game.hpp"
#include "Text.hpp"

class Game;
class Text;

class FinishScreen : public Actor {
public:
  FinishScreen(Game *g);

  virtual void draw() const override;
  virtual void update() override;

  enum class State { SHOW = 1, SHOWING, HIDDING, HIDDEN };

  void setState(State state);

  ~FinishScreen();

private:
  Game *game;
  State state;
  float opacity;

  Text *gameOverText;
};

#endif // !FINISH_SCREEN_HPP
