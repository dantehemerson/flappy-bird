#pragma once
#ifndef R_HPP
#define R_HPP

#include <array>
#include <map>
#include <string>

#include <raylib.h>

using namespace std;

class R {
public:
  static R &getSingleton();

  void loadResources();

  enum TextureIds { FLAPPY_SPRITES = 1 };

  enum FontIds { ART = 1 };

  Texture2D getTexture(const TextureIds &textureId) const;
  Font getFont(const FontIds &fontId) const;

  ~R();

private:
  R();
  static R *instance;

  unordered_map<TextureIds, Texture2D> textures;
  unordered_map<FontIds, Font> fonts;
};

#endif // !R_HPP
