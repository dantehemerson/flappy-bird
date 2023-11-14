#pragma once
#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <list>
#include <string>

#include "ControllableObject.hpp"
#include "Peripheral.hpp"

using namespace std;

class Control {
public:
  typedef struct {
    ControllableObject::action_t action;
    string name;
    Peripheral *peripheral;
    Peripheral::component_t component;
    Peripheral::event_t oldEvent;
    Peripheral::event_t event;
  } association_t;

  void addActionName(ControllableObject::action_t action, string name);

  void setActionPeripheral(ControllableObject::action_t action, Peripheral *peripheral,
                           Peripheral::component_t component, Peripheral::event_t event);

  string getNameAction(ControllableObject::action_t);

  void setOwner(ControllableObject *);

  ControllableObject *getOwner() const;

  void update();

  void reset();

private:
  ControllableObject *owner;
  list<association_t> associations;
  list<association_t>::iterator associationsIter;
};

#endif // !CONTROL_HPP