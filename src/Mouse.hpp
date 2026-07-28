#pragma once
#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <array>
#include <raylib.h>

#include "Peripheral.hpp"

class Mouse : public Peripheral {
public:
  Mouse();

  virtual state_t getState(component_t component) override;

  virtual component_t getChange() override;

  virtual void reset() override;

  inline void poll() {}

  ~Mouse();

private:
  // Support raylib's MouseButton enum (LEFT = 0, RIGHT = 1, MIDDLE = 2)
  std::array<bool, 3> oldState{};
};

#endif // !MOUSE_HPP
