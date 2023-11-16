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

  void setDisplacementY(const float &desplacementY) { this->displacement.y += desplacementY; }
  void setDisplacementX(const float &desplacementX) { this->displacement.x += desplacementX; }

  int getTicks() const;

private:
  Actor *owner;
  R::TextureIds textureId;
  Rectangle source;
  int ticks;
  // Indicates if the frame should be drawn centered or not.
  bool center;
  Vector2 displacement;
};
#endif // !FRAME_HPP
