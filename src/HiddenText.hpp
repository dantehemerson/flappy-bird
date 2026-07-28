#pragma once
#ifndef HIDDEN_TEXT_HPP
#define HIDDEN_TEXT_HPP

#include "Text.hpp"

class HiddenText : public Text {
public:
  using Text::Text;

  void draw() const override;

  void show();
  void hide();

private:
  bool visible = true;
};

#endif // !HIDDEN_TEXT_HPP
