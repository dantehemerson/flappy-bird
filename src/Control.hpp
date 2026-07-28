#pragma once
#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <list>

#include "ControllableObject.hpp"
#include "Peripheral.hpp"

using namespace std;

class Control {
public:
  typedef struct {
    ControllableObject::action_t action;
    Peripheral *peripheral;
    Peripheral::component_t component;
    Peripheral::event_t oldEvent;
    Peripheral::event_t event;
  } binding_t;

  void addActionPeripheral(ControllableObject::action_t action, Peripheral *peripheral,
                           Peripheral::component_t component, Peripheral::event_t event);

  void setOwner(ControllableObject *);

  ControllableObject *getOwner() const;

  void update();

  void reset();

private:
  ControllableObject *owner;
  list<binding_t> bindings;
};

#endif // !CONTROL_HPP
