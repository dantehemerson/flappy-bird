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
  float initialX = this->getInitialX();

  for (auto &c : this->text) {
    DrawTextureRec(R::getSingleton().getTexture(R::TextureIds::FLAPPY_SPRITES),
                   Utils::fontSources[Utils::FONT_SIZE::LARGE][c], {initialX, this->position.y},
                   WHITE);
    initialX += Utils::fontSources[Utils::FONT_SIZE::LARGE][c].width + WITH_SCALE(1.5);
  }
}

void Text::update() {}

void Text::setText(const string &text, const TEXT_ALIGN &align) {
  this->text = text;
  this->align = align;
  this->textWidth = text.size() * Utils::fontSources[Utils::FONT_SIZE::LARGE]['0'].width;
  this->textWidth += std::max(static_cast<float>(text.size() - 1), 0.0f) * WITH_SCALE(1.5);
}

float Text::getInitialX() const {
  switch (this->align) {
    case TEXT_ALIGN::LEFT:
      return this->position.x;
    case TEXT_ALIGN::CENTER:
      return this->position.x - this->textWidth / 2;
    case TEXT_ALIGN::RIGHT:
      return this->position.x - this->textWidth;
  }
}
