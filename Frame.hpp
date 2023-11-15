#pragma once

#ifndef FRAME_HPP
#define FRAME_HPP

#include "Actor.hpp"
#include "R.hpp"
#include <raylib.h>

class Frame : public Actor {
public:
  Frame(Actor *owner, R::TextureIds textureId, const Rectangle &source, int ticks,
        const bool center = false);

  virtual void draw() const override;
  virtual void update() override;

  bool isCentered() const;
  float getWidth() const;
  float getHeight() const;

  int getTicks() const;

private:
  Actor *owner;
  R::TextureIds textureId;
  Rectangle source;
  int ticks;

  // Indicates if the frame should be drawn centered or not.
  bool center;
};
#endif // !FRAME_HPP
