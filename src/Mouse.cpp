#include "Mouse.hpp"
#include "Peripheral.hpp"
#include <raylib.h>

Mouse::Mouse() {}

Peripheral::state_t Mouse::getState(state_t component) {
  if (IsMouseButtonPressed(component)) {
    return true;
  } else {
    return INVALID_STATE;
  }
}

Peripheral::component_t Mouse::getChange() {
  for (int i = 0; i < this->oldState.size(); i++) {
    bool value = IsMouseButtonPressed(i);
    if (value != oldState[i]) {
      oldState[i] = value;
      return i;
    }
  }

  return INVALID_COMPONENT;
}

void Mouse::reset() {
  for (int i = 0; i < this->oldState.size(); i++) {
    oldState[i] = false;
  }
}

Mouse::~Mouse() {}
