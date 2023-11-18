#include <algorithm>

#include "Logger.h"
#include "R.hpp"
#include "Text.hpp"
#include "Utils.hpp"
#include <raylib.h>

using namespace std;

Text::Text(const Utils::FONT_SIZE &size, const float &x, const float &y) : size(size) {
  this->position = {x, y};
}

void Text::draw() const {
  float initialX = this->position.x;
  for (auto &c : this->text) {
    DrawTextureRec(R::getSingleton().getTexture(R::TextureIds::FLAPPY_SPRITES),
                   Utils::fontSources[Utils::FONT_SIZE::LARGE][c], {initialX, this->position.y},
                   WHITE);
    initialX += Utils::fontSources[Utils::FONT_SIZE::LARGE][c].width + WITH_SCALE(1.5);
  }
}

void Text::update() {}

void Text::setText(const string &text) {
  this->text = text;
}
