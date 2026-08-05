#pragma once
#ifndef PIPES_MANAGER_HPP
#define PIPES_MANAGER_HPP

#include <vector>

#include "Actor.hpp"

using namespace std;

class Bird;
class Pipe;

class PipesManager : public Actor {
public:
  PipesManager();

  enum class PipesState : size_t { STOPPED = 1, MOVING };

  virtual void draw() const override;
  virtual void update() override;

  void resetPipes();
  void setVelocityX(const float &velocity);

  void setState(PipesState state);

  bool hasBirdPassedPipe(Bird *bird);
  bool hasBirdOrBulletsCollided(const Bird *bird) const;

private:
  vector<Pipe *> pipes;
  PipesState state;
  float velocityX;
  float distanceBetweenPipes;
};

#endif // !PIPES_MANAGER_HPP
