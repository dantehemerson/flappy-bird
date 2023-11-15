#include "Frame.hpp"
#include "Logger.h"
#include "R.hpp"

Frame::Frame(Actor *_owner, R::TextureIds _textureId, const Rectangle &_source, int _ticks,
             const float _xDesp, const float _yDesp)
    : owner(_owner), textureId(_textureId), source(_source), ticks(_ticks), xDesp(_xDesp),
      yDesp(_yDesp) {}

void Frame::draw() const {
  DrawTexturePro(
      R::getSingleton().getTexture(this->textureId), this->source,
      {this->owner->position.x, this->owner->position.y, this->getWidth(), this->getHeight()},
      {this->getWidth() / 2, this->getHeight() / 2}, this->owner->rotation, WHITE);
}

void Frame::update() {}

int Frame::getTicks() const {
  return ticks;
}

float Frame::getWidth() const {
  return this->source.width;
}

float Frame::getHeight() const {
  return this->source.height;
}