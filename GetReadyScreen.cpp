#include "GetReadyScreen.hpp"
#include "Globals.hpp"
#include "R.hpp"
#include "Utils.hpp"
#include <raylib.h>

GetReadyScreen::GetReadyScreen() {
  this->setState(State::SHOW);
}

void GetReadyScreen::draw() const {
  static const float topY = WITH_SCALE(50);

  // Get Ready
  DrawTextureRec(R::getSingleton().getTexture(R::TextureIds::FLAPPY_SPRITES),
                 {WITH_SCALE(295), WITH_SCALE(59), WITH_SCALE(92), WITH_SCALE(25)},
                 {Globals::Settings::WIDTH / 2.0 - WITH_SCALE(92) / 2.0, topY},
                 CLITERAL(Color){255, 255, 255,
                                 static_cast<unsigned char>(static_cast<int>(this->opacity))});

  // Tap
  DrawTextureRec(R::getSingleton().getTexture(R::TextureIds::FLAPPY_SPRITES),

                 {WITH_SCALE(292), WITH_SCALE(91), WITH_SCALE(57), WITH_SCALE(49)},
                 {Globals::Settings::WIDTH / 2.0 - WITH_SCALE(57) / 2.0, topY + WITH_SCALE(50)},
                 CLITERAL(Color){255, 255, 255,
                                 static_cast<unsigned char>(static_cast<int>(this->opacity))});
}

void GetReadyScreen::update() {
  if (this->state == State::HIDDING) {
    this->opacity -= 7;

    if (this->opacity <= 0) {
      this->setState(State::HIDDEN);
    }
  }
}

void GetReadyScreen::setState(State state) {
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
