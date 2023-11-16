#pragma once
#ifndef PIPE_HPP
#define PIPE_HPP

#include "Actor.hpp"
#include "Game.hpp"
#include "Sprite.hpp"

class Pipe : public Actor {
public:
  Pipe();

  virtual void draw() const override;
  virtual void update() override;

  void setVelocityX(const float &velocity) { this->velocityX = velocity; }

private:
  void initializeSprites();

  Sprite spritePipeTop;
  Sprite spritePipeBottom;
  float velocityX;
};

#endif // !PIPE_HPP
