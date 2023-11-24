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
  this->sounds.insert({R::SoundId::WING, LoadSound("resources/sounds/sfx_wing.ogg")});
  this->sounds.insert({R::SoundId::POINT, LoadSound("resources/sounds/sfx_point.ogg")});
  this->sounds.insert({R::SoundId::HIT, LoadSound("resources/sounds/sfx_hit.ogg")});
  this->sounds.insert({R::SoundId::DIE, LoadSound("resources/sounds/sfx_die.ogg")});
  this->sounds.insert({R::SoundId::SWOOSHING, LoadSound("resources/sounds/sfx_swooshing.ogg")});
}

Texture2D R::getTexture(const R::TextureIds &textureId) const {
  return this->textures.at(textureId);
}

Font R::getFont(const R::FontIds &fontId) const {
  return this->fonts.at(fontId);
}

Sound R::getSound(const R::SoundId &soundId) const {
  return this->sounds.at(soundId);
}

R::~R() {
  for (auto it = this->textures.begin(); it != this->textures.end(); it++) {
    UnloadTexture(it->second);
  }

  for (auto it = this->fonts.begin(); it != this->fonts.end(); it++) {
    UnloadFont(it->second);
  }

  for (auto it = this->sounds.begin(); it != this->sounds.end(); it++) {
    UnloadSound(it->second);
  }

  this->textures.clear();
  this->fonts.clear();
  this->sounds.clear();

  delete this->instance;
}
