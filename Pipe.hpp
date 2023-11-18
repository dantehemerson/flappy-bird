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

  void setHasPassedBird(const bool &hasPassedBird);

  float getWidth() const;
  bool hasPassedBird() const;

private:
  void initializeSprites();
  bool _hasPassedBird;

  Sprite spritePipeTop;
  Sprite spritePipeBottom;
};

#endif // !PIPE_HPP
