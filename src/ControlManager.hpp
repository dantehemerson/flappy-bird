#pragma once
#ifndef CONTROLMANAGER_HPP
#define CONTROLMANAGER_HPP

#include <vector>

#include "Control.hpp"
#include "Peripheral.hpp"

using namespace std;

#define MAX_PERIPHERALS 5

class ControlManager {
public:
  ControlManager();

  typedef struct {
    Peripheral *peripheral;
    Peripheral::component_t component;
  } change_t;

  change_t getChange();

  int addControl(Control *control);

  int addPeripheral(Peripheral *peripheral);

  Control *getControl(int index);

  Peripheral *getPeripheral(int index);

  void update();

  ~ControlManager();

private:
  vector<Control *> controls;
  vector<Control *>::iterator controlsIter;
  vector<Peripheral *> peripherals;
  vector<Peripheral *>::iterator peripheralsIter;
  int oldState[MAX_PERIPHERALS];
};

#endif // CONTROLMANAGER_HPP
