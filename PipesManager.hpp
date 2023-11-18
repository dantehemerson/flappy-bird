#pragma once
#ifndef PIPES_MANAGER_HPP
#define PIPES_MANAGER_HPP

#include <vector>

#include "Actor.hpp"
#include "Bird.hpp"
#include "Game.hpp"
#include "Pipe.hpp"
#include "Sprite.hpp"

using namespace std;

class Bird;
class Pipe;

class PipesManager : public Actor {
public:
  PipesManager(Bird *bird);

  virtual void draw() const override;
  virtual void update() override;

  void resetPipes();
  void setVelocityX(const float &velocity);

  bool hasBirdPassedPipe();
  bool hasBirdCollided() const;

private:
  vector<Pipe *> pipes;
  Bird *bird;
  float velocityX;
  float distanceBetweenPipes;
};

#endif // !PIPES_MANAGER_HPP
