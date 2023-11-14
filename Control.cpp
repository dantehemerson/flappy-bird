#include "Control.hpp"

using namespace std;

void Control::addActionName(ControllableObject::action_t action, string name) {
  association_t association;
  association.action = action;
  association.name = name;
  association.peripheral = NULL;
  association.component = 0;
  associations.push_back(association);
}

void Control::setActionPeripheral(ControllableObject::action_t action, Peripheral *peripheral,
                                  Peripheral::component_t component, Peripheral::event_t event) {
  for (associationsIter = associations.begin(); associationsIter != associations.end();
       associationsIter++) {
    if (associationsIter->action == action) {
      associationsIter->peripheral = peripheral;
      associationsIter->component = component;
      associationsIter->event = event;
      associationsIter->oldEvent = Peripheral::NO_EVENT;
      return;
    }
  }
}

void Control::setOwner(ControllableObject *owner) {
  this->owner = owner;
}

ControllableObject *Control::getOwner() const {
  return owner; /* Retorna el apuntador al due�o del control. */
}

void Control::update() {
  int doActionOrder;
  Peripheral::state_t currentState;
  Peripheral::event_t previousEvent;
  for (associationsIter = associations.begin(); associationsIter != associations.end();
       associationsIter++) {

    currentState = associationsIter->peripheral->getState(associationsIter->component);
    previousEvent = associationsIter->oldEvent;

    doActionOrder = false;

    switch (associationsIter->event) {
      case Peripheral::ON_PRESSING:
        if (currentState != INVALID_STATE) {
          doActionOrder = true;
        }
        break;

      case Peripheral::ON_PRESS:
        if ((previousEvent == Peripheral::ON_RELEASE) && (currentState != INVALID_STATE)) {
          associationsIter->oldEvent = Peripheral::ON_PRESS;
          doActionOrder = true;
        } else if (currentState == INVALID_STATE) {
          associationsIter->oldEvent = Peripheral::ON_RELEASE;
        }
        break;

      case Peripheral::ON_RELEASE:
        if ((previousEvent == Peripheral::ON_PRESS) && (currentState == INVALID_STATE)) {
          associationsIter->oldEvent = Peripheral::ON_RELEASE;
          doActionOrder = true;
        } else if (currentState != INVALID_STATE) {
          associationsIter->oldEvent = Peripheral::ON_PRESS;
        }
        break;

      case Peripheral::ON_RELEASING:
        if (currentState == INVALID_STATE) {
          doActionOrder = true;
        }
        break;

      default:
        break;
    }

    if (doActionOrder) {
      owner->doAction(associationsIter->action, currentState);
    }
  }
}

string Control::getNameAction(ControllableObject::action_t action) {
  for (associationsIter = associations.begin(); associationsIter != associations.end();
       associationsIter++) {
    if (associationsIter->action == action) {
      return associationsIter->name;
    }
  }
  return "";
}