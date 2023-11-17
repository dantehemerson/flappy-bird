#pragma once
#ifndef PIPES_MANAGER_HPP
#define PIPES_MANAGER_HPP

#include <vector>

#include "Actor.hpp"
#include "Game.hpp"
#include "Pipe.hpp"
#include "Sprite.hpp"

using namespace std;

class PipesManager : public Actor {
public:
  PipesManager();

  virtual void draw() const override;
  virtual void update() override;

  void resetPipes();
  void setVelocityX(const float &velocity);

private:
  vector<Pipe *> pipes;

  float velocityX;
  float distanceBetweenPipes;
};

#endif // !PIPES_MANAGER_HPP
