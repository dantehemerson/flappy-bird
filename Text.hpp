#pragma once
#ifndef TEXT_HPP
#define TEXT_HPP

#include <string>

#include "Actor.hpp"
#include "Game.hpp"
#include "Utils.hpp"

using namespace std;

class Text : public Actor {
public:
  Text(const Utils::FONT_SIZE &size, const float &x, const float &y);

  virtual void draw() const override;
  virtual void update() override;

  void setText(const string &text);

private:
  Utils::FONT_SIZE size;
  string text;
};

#endif // !TEXT_HPP
