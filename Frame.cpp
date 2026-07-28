#include "Frame.hpp"
#include "Actor.hpp"
#include "R.hpp"

#include <raylib.h>

Frame::Frame(Actor *_owner, R::TextureIds _textureId, const Rectangle &_source, int _ticks,
             const bool center)
    : owner(_owner), textureId(_textureId), source(_source), ticks(_ticks), center(center),
      displacement({0, 0}) {}

void Frame::draw() const {
  Vector2 origin =
      this->center ? Vector2{this->getWidth() / 2, this->getHeight() / 2} : Vector2{0, 0};
  float positionX =
      this->center ? this->owner->position.x - this->getWidth() / 2 : this->owner->position.x;
  float positionY =
      this->center ? this->owner->position.y - this->getHeight() / 2 : this->owner->position.y;

  DrawTexturePro(R::getSingleton().getTexture(this->textureId), this->source,
                 {positionX + this->displacement.x, positionY + this->displacement.y,
                  this->getWidth(), this->getHeight()},
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
