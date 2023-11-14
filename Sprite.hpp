#pragma once
#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <vector>

#include "Frame.hpp"
#include "R.hpp"
#include <raylib.h>

using namespace std;

class Actor;

class Sprite {
public:
  Sprite(Actor *owner = nullptr);
  void draw() const;

  void update();

  void reinit();

  // Only works if the sprite is not repeating.
  bool animationFinish() const;

  void setOwner(Actor *owner);

  // Set if the sprite will repeat or not.
  void setRepeat(bool repeat);

  void addFrame(R::TextureIds idImage, const Rectangle &source, int ticks,
                const float xDesp = 0.0f, const float yDesp = 0.0f);

  void setActualTick(int tick);
  void setActualFrame(int frame);

  float getWidth() const;
  float getHeight() const;

  ~Sprite();

private:
  Actor *owner;
  std::vector<Frame> frames;
  int actualTick;
  int actualFrame;
  bool repeat;
  bool finish;
};

#endif // !SPRITE_HPP
