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

  enum class SurfaceState : size_t { SURFACE_MOVING, SURFACE_STOPPED };

  void setVelocityX(const float &velocity);

private:
  Game *game;
  array<SurfaceTile, 2> tiles;
  SurfaceState state;
};

#endif // !SURFACE_HPP