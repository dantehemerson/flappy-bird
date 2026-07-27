#include <algorithm>

#include "R.hpp"
#include "Text.hpp"
#include "Utils.hpp"
#include <raylib.h>

using namespace std;

Text::Text(const Utils::FONT_SIZE &size, const float &x, const float &y, const TEXT_ALIGN &align) : size(size), align(align) {
  this->position = {x, y};
}

void Text::draw() const {
  float initialX = this->getInitialX();

  for (auto &c : this->text) {
    DrawTextureRec(R::getSingleton().getTexture(R::TextureIds::FLAPPY_SPRITES),
                   Utils::fontSources[size][c], {initialX, this->position.y},
                   WHITE);
    initialX += Utils::fontSources[size][c].width + WITH_SCALE(1.5);
  }
}

void Text::update() {}

void Text::setText(const string &text) {
  this->text = text;
  this->textWidth = text.size() * Utils::fontSources[size]['0'].width;
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
