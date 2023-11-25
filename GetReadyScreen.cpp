#include "GetReadyScreen.hpp"

#include "Globals.hpp"
#include "R.hpp"
#include "Utils.hpp"
#include <raylib.h>

GetReadyScreen::GetReadyScreen() {}

void GetReadyScreen::draw() const {

  static const float topY = WITH_SCALE(59);
  DrawTextureRec(R::getSingleton().getTexture(R::TextureIds::FLAPPY_SPRITES),
                 {WITH_SCALE(295), WITH_SCALE(59), WITH_SCALE(92), WITH_SCALE(25)},
                 {Globals::Settings::WIDTH / 2 - WITH_SCALE(92) / 2, topY}, WHITE);

  DrawTextureRec(R::getSingleton().getTexture(R::TextureIds::FLAPPY_SPRITES),
                 {WITH_SCALE(292), WITH_SCALE(91), WITH_SCALE(57), WITH_SCALE(49)},
                 {Globals::Settings::WIDTH / 2 - WITH_SCALE(57) / 2, topY + WITH_SCALE(30)},
                 WHITE);
}

void GetReadyScreen::update() {}
