#include "Sprite.hpp"

#include "Actor.hpp"

Sprite::Sprite(Actor *owner) : owner(owner) {
  this->actualFrame = 0;
  this->actualTick = 0;
  this->repeat = false;
  this->finish = true;
}

void Sprite::draw() const {
  frames.at(actualFrame).draw();
}

void Sprite::update() {
  if (frames.size() <= 1)
    return;

  if (actualTick > frames.at(actualFrame).getTicks()) {
    actualTick = 0;
    actualFrame++;
    if (actualFrame >= static_cast<int>(frames.size())) {
      actualFrame = repeat ? 0 : frames.size() - 1;
      if (!repeat) {
        finish = true;
      }
    } else {
      static int dif;
      dif = frames.at(actualFrame - 1).getWidth() - frames.at(actualFrame).getWidth();
      owner->position.x = this->owner->position.x + dif / 2;
    }
  } else {
    actualTick++;
  }
}

void Sprite::setOwner(Actor *actor) {
  this->owner = actor;
}

void Sprite::setRepeat(bool repeat) {
  this->repeat = repeat;
}

void Sprite::reinit() {
  actualTick = 0;
  actualFrame = 0;
  finish = false;
}

float Sprite::getWidth() const {
  return frames.at(actualFrame).getWidth();
}

bool Sprite::animationFinish() const {
  return finish;
}

void Sprite::addFrame(R::TextureIds textureId, const Rectangle &source, int ticks,
                      const float xDesp, const float yDesp) {
  Frame frame(this->owner, textureId, source, ticks, xDesp, yDesp);
  frames.push_back(frame);
}

void Sprite::setActualTick(int indexTick) {
  actualTick = indexTick;
}

void Sprite::setActualFrame(int indexFrame) {
  actualFrame = indexFrame;
}

Sprite::~Sprite() {
  frames.clear();
}