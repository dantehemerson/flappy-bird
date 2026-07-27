#ifndef FINISH_SCREEN_HPP
#define FINISH_SCREEN_HPP

#include "ControllableActor.hpp"
#include "Text.hpp"

class Game;

class FinishScreen : public ControllableActor {
public:
  FinishScreen(Game *g);

  virtual void draw() const override;
  virtual void update() override;
  virtual void doAction(action_t action, int magnitute) override;

  enum Actions { PLAY_AGAIN = 1 };
  enum State { SHOW = 1, SHOWING, HIDDING, HIDDEN };

  void setState(State state);

  ~FinishScreen();

private:
  void drawMedal(int score) const;

  Game *game;
  State state;
  float opacity;

  Text *gameOverText;
  Text *bestScoreText;
};

#endif // !FINISH_SCREEN_HPP
