#pragma once

#ifndef FRAME_HPP
#define FRAME_HPP

#include "Actor.hpp"
#include "R.hpp"
#include <raylib.h>

class Frame : public Actor {
public:
  Frame(Actor *owner, R::TextureIds textureId, const Rectangle &source, int ticks,
        const float xDesp = 0.0f, const float yDesp = 0.0F);

  virtual void draw() const override;
  virtual void update() override;

  float getWidth() const;
  int getTicks() const;

private:
  Actor *owner;
  R::TextureIds textureId;
  Rectangle source;
  int ticks;
  float xDesp;
  float yDesp;
};
#endif // !FRAME_HPP
