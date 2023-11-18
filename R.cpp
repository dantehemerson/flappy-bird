#include "R.hpp"

#include <array>
#include <stdexcept>
#include <stdio.h>

#include "Logger.h"
#include <raylib.h>

using namespace std;

R *R::instance = nullptr;

R::R() {}

R &R::getSingleton() {
  if (!instance) {
    instance = new R();
  }

  return *instance;
}

void R::loadResources() {
  this->textures.insert(
      {R::TextureIds::FLAPPY_SPRITES, LoadTexture("resources/flappy-bird_x4.png")});
}

Texture2D R::getTexture(const R::TextureIds &textureId) const {
  return this->textures.at(textureId);
}

Font R::getFont(const R::FontIds &fontId) const {
  return this->fonts.at(fontId);
}

R::~R() {
  LogAlert << "Calling Rersources destructor" << endl;

  for (auto it = this->textures.begin(); it != this->textures.end(); it++) {
    UnloadTexture(it->second);
  }

  for (auto it = this->fonts.begin(); it != this->fonts.end(); it++) {
    UnloadFont(it->second);
  }

  this->textures.clear();
  this->fonts.clear();

  delete this->instance;
}
