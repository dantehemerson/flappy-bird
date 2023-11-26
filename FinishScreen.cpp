#include "FinishScreen.hpp"
#include "Globals.hpp"
#include "Logger.h"
#include "R.hpp"
#include "Utils.hpp"
#include <raylib.h>

FinishScreen::FinishScreen(Game *g) : game(g) {
  this->setState(State::SHOW);
}

void FinishScreen::draw() const {
  static const float topY = WITH_SCALE(50);

  // Game Over
  DrawTextureRec(R::getSingleton().getTexture(R::TextureIds::FLAPPY_SPRITES),
                 {WITH_SCALE(395), WITH_SCALE(59), WITH_SCALE(96), WITH_SCALE(21)},
                 {Globals::Settings::WIDTH / 2 - WITH_SCALE(96) / 2, topY},
                 CLITERAL(Color){255, 255, 255,
                                 static_cast<unsigned char>(static_cast<int>(this->opacity))});

  // Board (Medal, Score, Best)
  DrawTextureRec(R::getSingleton().getTexture(R::TextureIds::FLAPPY_SPRITES),
                 {WITH_SCALE(3), WITH_SCALE(259), WITH_SCALE(113), WITH_SCALE(57)},
                 {Globals::Settings::WIDTH / 2 - WITH_SCALE(113) / 2, topY + WITH_SCALE(34)},
                 CLITERAL(Color){255, 255, 255,
                                 static_cast<unsigned char>(static_cast<int>(this->opacity))});

  // Play Green Button
  DrawTextureRec(R::getSingleton().getTexture(R::TextureIds::FLAPPY_SPRITES),
                 {WITH_SCALE(354), WITH_SCALE(118), WITH_SCALE(52), WITH_SCALE(34)},
                 {Globals::Settings::WIDTH / 2 - WITH_SCALE(52) / 2, topY + WITH_SCALE(120)},
                 CLITERAL(Color){255, 255, 255,
                                 static_cast<unsigned char>(static_cast<int>(this->opacity))});
}

void FinishScreen::update() {}

void FinishScreen::setState(State state) {
  this->state = state;

  switch (state) {
    case State::SHOW:
      this->opacity = 255;
      break;
    case State::HIDDING:
      this->opacity = 255;
      break;
    case State::HIDDEN:
      this->opacity = 0;
      break;
  }
}
