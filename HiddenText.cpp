#include "HiddenText.hpp"
#include "Text.hpp"

void HiddenText::draw() const {
  if (!this->visible) {
    return;
  }

  Text::draw();
}

void HiddenText::show() {
  this->visible = true;
}
void HiddenText::hide() {
  this->visible = false;
}
