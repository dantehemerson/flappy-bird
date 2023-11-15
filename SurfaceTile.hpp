#pragma once
#ifndef SURFACE_TILEHPP
#define SURFACE_TILEHPP

#include "Actor.hpp"
#include "Game.hpp"
#include "Sprite.hpp"

class SurfaceTile : public Actor {
public:
  SurfaceTile();

  virtual void draw() const override;
  virtual void update() override;

  void setVelocityX(const float &velocity) { this->velocityX = velocity; }

private:
  void initializeSprites();

  Sprite sprite;
  float velocityX;
};

#endif // !SURFACE_TILEHPP