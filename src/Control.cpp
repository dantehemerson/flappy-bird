#include "Control.hpp"
#include "ControllableObject.hpp"
#include "Peripheral.hpp"

using namespace std;

void Control::addActionPeripheral(ControllableObject::action_t action, Peripheral *peripheral,
                                  Peripheral::component_t component, Peripheral::event_t event) {
  binding_t binding;
  binding.action = action;
  binding.peripheral = peripheral;
  binding.component = component;
  binding.event = event;
  binding.oldEvent = Peripheral::NO_EVENT;
  bindings.push_back(binding);
}

void Control::setOwner(ControllableObject *owner) {
  this->owner = owner;
}

ControllableObject *Control::getOwner() const {
  return owner;
}

void Control::update() {
  for (auto &binding : bindings) {
    Peripheral::state_t currentState = binding.peripheral->getState(binding.component);
    Peripheral::event_t previousEvent = binding.oldEvent;
    bool doActionOrder = false;

    switch (binding.event) {
      case Peripheral::ON_PRESSING:
        if (currentState != INVALID_STATE)
          doActionOrder = true;
        break;
      case Peripheral::ON_PRESS:
        if ((previousEvent == Peripheral::ON_RELEASE) && (currentState != INVALID_STATE)) {
          binding.oldEvent = Peripheral::ON_PRESS;
          doActionOrder = true;
        } else if (currentState == INVALID_STATE) {
          binding.oldEvent = Peripheral::ON_RELEASE;
        }
        break;
      case Peripheral::ON_RELEASE:
        if ((previousEvent == Peripheral::ON_PRESS) && (currentState == INVALID_STATE)) {
          binding.oldEvent = Peripheral::ON_RELEASE;
          doActionOrder = true;
        } else if (currentState != INVALID_STATE) {
          binding.oldEvent = Peripheral::ON_PRESS;
        }
        break;
      case Peripheral::ON_RELEASING:
        if (currentState == INVALID_STATE)
          doActionOrder = true;
        break;
      default:
        break;
    }

    if (doActionOrder) {
      owner->doAction(binding.action, currentState);
    }
  }
}
