#pragma once

#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include "Peripheral.hpp"
#include <raylib.h>

#define MAX_KEY KEY_KB_MENU

using namespace std;

class Keyboard : public Peripheral {
public:
  Keyboard();

  virtual state_t getState(component_t component) override;

  virtual component_t getChange() override;

  virtual void reset() override;

  inline void poll(){};

  ~Keyboard();

private:
  bool oldState[MAX_KEY]; /* Store key's status.*/
};

#endif // !KEYBOARD_HPP
