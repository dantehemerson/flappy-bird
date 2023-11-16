#include "Frame.hpp"
#include "Logger.h"
#include "R.hpp"

Frame::Frame(Actor *_owner, R::TextureIds _textureId, const Rectangle &_source, int _ticks,
             const bool center)
    : owner(_owner), textureId(_textureId), source(_source), ticks(_ticks), center(center) {}

void Frame::draw() const {
  Vector2 origin =
      this->center ? Vector2{this->getWidth() / 2, this->getHeight() / 2} : Vector2{0, 0};

  DrawTexturePro(
      R::getSingleton().getTexture(this->textureId), this->source,
      {this->owner->position.x, this->owner->position.y, this->getWidth(), this->getHeight()},
      origin, this->owner->rotation, WHITE);
}

void Frame::update() {}

int Frame::getTicks() const {
  return ticks;
}

bool Frame::isCentered() const {
  return this->center;
}

float Frame::getWidth() const {
  return this->source.width;
}

float Frame::getHeight() const {
  return this->source.height;
}