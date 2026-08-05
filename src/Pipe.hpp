#pragma once
#ifndef PIPE_HPP
#define PIPE_HPP

#include "Actor.hpp"
#include "Bird.hpp"
#include "Bullet.hpp"
#include "Sprite.hpp"

class Bird;
class Bullet;

class Pipe : public Actor {
public:
  Pipe();

  virtual void draw() const override;
  virtual void update() override;

  void setHasPassedBird(const bool &hasPassedBird);

  float getWidth() const;
  bool hasPassedBird() const;
  bool hasCollided(const Bird *bird) const;
  bool hasCollided(const Bullet *bullet) const;

private:
  void initializeSprites();
  bool _hasPassedBird;

  Sprite spritePipeTop;
  Sprite spritePipeBottom;
};

#endif // !PIPE_HPP
