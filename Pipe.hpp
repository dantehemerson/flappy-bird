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

private:
  void initializeSprites();

  Sprite spritePipeTop;
  Sprite spritePipeBottom;
};

#endif // !PIPE_HPP
