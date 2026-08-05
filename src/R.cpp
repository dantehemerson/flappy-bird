#include "R.hpp"
#include "Utils.hpp"

#include <raylib.h>
#include <stdio.h>

using namespace std;

R *R::instance = nullptr;

R::R() {
  this->medalRectangles = {
      {R::Medal::BRONZE, {WITH_SCALE(121), WITH_SCALE(258), WITH_SCALE(22), WITH_SCALE(22)}},
      {R::Medal::SILVER, {WITH_SCALE(146), WITH_SCALE(258), WITH_SCALE(22), WITH_SCALE(22)}},
      {R::Medal::GOLD_MEDAL, {WITH_SCALE(121), WITH_SCALE(282), WITH_SCALE(22), WITH_SCALE(22)}},
      {R::Medal::PLATINUM, {WITH_SCALE(112), WITH_SCALE(477), WITH_SCALE(22), WITH_SCALE(22)}},
  };
}

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
  this->sounds.insert({R::SoundId::SHOOT, LoadSound("resources/sounds/sfx_shoot.wav")});
}

Texture2D R::getTexture(const R::TextureIds &textureId) const {
  return this->textures.at(textureId);
}

Font R::getFont(const R::FontIds &fontId) const {
  return this->fonts.at(fontId);
}

const Sound &R::getSound(const R::SoundId &soundId) const {
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
