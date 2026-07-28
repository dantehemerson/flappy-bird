#pragma once
#ifndef R_HPP
#define R_HPP

#include <unordered_map>

#include <raylib.h>

using namespace std;

class R {
public:
  static R &getSingleton();

  void loadResources();

  enum TextureIds { FLAPPY_SPRITES = 1 };
  enum FontIds { FLAPPY_FONT = 1 };
  enum SoundId { DIE = 1, HIT, POINT, SWOOSHING, WING };
  enum Medal { BRONZE = 1, SILVER, GOLD_MEDAL, PLATINUM };

  unordered_map<Medal, Rectangle> medalRectangles;

  Texture2D getTexture(const TextureIds &textureId) const;
  Font getFont(const FontIds &fontId) const;
  const Sound &getSound(const SoundId &soundId) const;

  ~R();

private:
  R();
  static R *instance;

  unordered_map<TextureIds, Texture2D> textures;
  unordered_map<FontIds, Font> fonts;
  unordered_map<SoundId, Sound> sounds;
};

#endif // !R_HPP
