#pragma once
#ifndef TEXT_HPP
#define TEXT_HPP

#include <string>

#include "Actor.hpp"
#include "Utils.hpp"

using namespace std;

enum class TEXT_ALIGN { LEFT = 1, CENTER, RIGHT };

class Text : public Actor {
public:
  Text(const Utils::FONT_SIZE &size, const float &x, const float &y, const TEXT_ALIGN &align = TEXT_ALIGN::CENTER);

  virtual void draw() const override;
  virtual void update() override;


  void setText(const string &text);

private:
  Utils::FONT_SIZE size;
  string text;
  float textWidth;
  TEXT_ALIGN align;

  float getInitialX() const;
};

#endif // !TEXT_HPP
