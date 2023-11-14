#pragma once
#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <raylib.h>

class Actor {
public:
  explicit Actor(const float &x = 0.0f, const float &y = 0.0f);
  virtual void draw() const = 0;
  virtual void update() = 0;

  virtual ~Actor();

  Vector2 position;
};

#endif // !ACTOR_HPP