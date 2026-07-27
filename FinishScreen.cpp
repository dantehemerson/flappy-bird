#include "FinishScreen.hpp"
#include "Bird.hpp"
#include "Game.hpp"
#include "Globals.hpp"
#include "R.hpp"
#include "Text.hpp"
#include "Utils.hpp"
#include <cstddef>
#include <optional>
#include <raylib.h>
#include <string>

FinishScreen::FinishScreen(Game *g) : game(g) {
  this->setState(State::HIDDEN);
  this->scoreText =
      new Text(Utils::FONT_SIZE::SMALL, WITH_SCALE(121.5), WITH_SCALE(100), TEXT_ALIGN::RIGHT);
  this->bestScoreText =
      new Text(Utils::FONT_SIZE::SMALL, WITH_SCALE(121.5), WITH_SCALE(121), TEXT_ALIGN::RIGHT);
  this->bestScoreText->setText("9999");
}

void FinishScreen::draw() const {
  if (this->state == State::HIDDEN)
    return;

  static const float topY = WITH_SCALE(50);

  // Game Over
  DrawTextureRec(R::getSingleton().getTexture(R::TextureIds::FLAPPY_SPRITES),
                 {WITH_SCALE(395), WITH_SCALE(59), WITH_SCALE(96), WITH_SCALE(21)},
                 {Globals::Settings::WIDTH / 2.0 - WITH_SCALE(96) / 2.0, topY},
                 CLITERAL(Color){255, 255, 255,
                                 static_cast<unsigned char>(static_cast<int>(this->opacity))});

  // Board (Medal, Score, Best)
  DrawTextureRec(R::getSingleton().getTexture(R::TextureIds::FLAPPY_SPRITES),
                 {WITH_SCALE(3), WITH_SCALE(259), WITH_SCALE(113), WITH_SCALE(57)},
                 {Globals::Settings::WIDTH / 2.0 - WITH_SCALE(113) / 2.0, topY + WITH_SCALE(34)},
                 CLITERAL(Color){255, 255, 255,
                                 static_cast<unsigned char>(static_cast<int>(this->opacity))});

  this->drawMedal(this->score);
  this->scoreText->draw();
  this->bestScoreText->draw();

  // Play Again Button
  DrawTextureRec(R::getSingleton().getTexture(R::TextureIds::FLAPPY_SPRITES),
                 {WITH_SCALE(354), WITH_SCALE(118), WITH_SCALE(52), WITH_SCALE(34)},
                 {Globals::Settings::WIDTH / 2.0 - WITH_SCALE(52) / 2.0, topY + WITH_SCALE(120)},
                 CLITERAL(Color){
                     255, 255, 255,
                     static_cast<unsigned char>(static_cast<int>(this->playAgainButtonOpacity))});
}

void FinishScreen::drawMedal(int score) const {
  std::optional<Rectangle> rect = nullopt;

  if (score > 10) {
    rect = R::getSingleton().medalRectangles[R::Medal::BRONZE];
  } else if (score > 20) {
    rect = R::getSingleton().medalRectangles[R::Medal::SILVER];
  } else if (score > 30) {
    rect = R::getSingleton().medalRectangles[R::Medal::GOLD_MEDAL];
  } else if (score > 40) {
    rect = R::getSingleton().medalRectangles[R::Medal::PLATINUM];
  } else {
    return;
  }

  if (rect != nullopt) {
    DrawTextureRec(R::getSingleton().getTexture(R::TextureIds::FLAPPY_SPRITES), rect.value(),
                   {130, 422},
                   CLITERAL(Color){255, 255, 255,
                                   static_cast<unsigned char>(static_cast<int>(this->opacity))});
  }
}

void FinishScreen::doAction(action_t action, int magnitute) {
  switch (action) {
    case FinishScreen::Actions::PLAY_AGAIN:
      if (this->state == State::SHOW) {
        this->game->execute(Game::GameActions::PLAY_AGAIN);
      }
      break;
  }
}

void FinishScreen::update() {
  if (this->state == State::START_SHOWING) {
    this->timer += GetFrameTime();

    this->opacity += (255 / 0.3f) * GetFrameTime();

    if (this->opacity >= 255) {
      this->opacity = 255;
    }

    if (this->timer > 0.3f) {
      this->playAgainButtonOpacity += (255 / 0.3f) * GetFrameTime();

      if (this->playAgainButtonOpacity >= 255) {
        this->playAgainButtonOpacity = 255;
      }
    }

    if (this->timer > 0.6f) {
      this->setState(State::SHOW);
    }
  }
}

void FinishScreen::setState(State state) {
  if (this->state == state)
    return;

  this->state = state;

  switch (state) {
    case State::SHOW:
      this->opacity = 255;
      this->playAgainButtonOpacity = 255;
      break;
    case State::HIDDING:
      this->opacity = 255;
      break;
    case State::HIDDEN:
      this->opacity = 0;
      break;
    case State::START_SHOWING:
      this->opacity = 0.0f;
      this->playAgainButtonOpacity = 0.0f;
      this->timer = 0.0f;
      break;
  }
}

void FinishScreen::setScore(int score) {
  this->score = score;
  this->scoreText->setText(to_string(score));
}

void FinishScreen::setBestScore(int bestScore) {
  this->bestScore = bestScore;
  this->bestScoreText->setText(to_string(bestScore));
}

FinishScreen::~FinishScreen() {
  delete this->scoreText;
  delete this->bestScoreText;
}
