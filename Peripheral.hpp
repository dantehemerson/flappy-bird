#pragma once
#ifndef PERIPHERAL_HPP
#define PERIPHERAL_HPP

#define INVALID_STATE -2
#define INVALID_COMPONENT -3

class Peripheral {
public:
  typedef enum {
    NO_EVENT = 0, // No event
    ON_PRESS,
    ON_PRESSING,
    ON_RELEASE,
    ON_RELEASING
  } event_t;

  typedef int state_t;

  // Indicates the component of the peripheral.
  // e.g. a key in the keyboard, a button in the mouse, etc.
  typedef int component_t;

  Peripheral();

  virtual state_t getState(component_t component) = 0;
  virtual component_t getChange() = 0;
  virtual void reset() = 0;
};

#endif // !PERIPHERAL_HPP
