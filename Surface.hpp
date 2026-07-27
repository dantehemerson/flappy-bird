#pragma once
#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <array>

#include "Actor.hpp"
#include "Game.hpp"
#include "Sprite.hpp"
#include "SurfaceTile.hpp"

using namespace std;

class Surface : public Actor {
public:
  Surface(Game *g);

  virtual void draw() const override;
  virtual void update() override;

  enum class SurfaceState : size_t { STOPPED = 1, MOVING };

  void setVelocityX(const float &velocity);

  void setState(SurfaceState state);

private:
  Game *game;
  array<SurfaceTile, 2> tiles;
  SurfaceState state;
};

#endif // !SURFACE_HPP
