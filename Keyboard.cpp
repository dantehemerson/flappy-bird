#include <iostream>

#include "Keyboard.hpp"
#include <raylib.h>

using namespace std;

Keyboard::Keyboard() {}

Peripheral::state_t Keyboard::getState(state_t component) {
  if (IsKeyDown(component)) {
    return true;
  } else {
    return INVALID_STATE;
  }
}

Peripheral::component_t Keyboard::getChange() {
  for (int i = 1; i < MAX_KEY; i++) {
    bool value = IsKeyDown(i);
    if (value != oldState[i]) {
      oldState[i] = value;
      return i;
    }
  }
  return INVALID_COMPONENT;
}

void Keyboard::reset() {
  for (int i = 1; i < MAX_KEY; i++) {
    oldState[i] = false;
  }
}

Keyboard::~Keyboard() {}