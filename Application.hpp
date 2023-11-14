#pragma once
#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Game.hpp"
#include "Keyboard.hpp"

class Application {
public:
  Application();

  void init(int argc, char **arv);

  void loop();

  Keyboard *getKeyboard() const;

  void quit();

  ~Application();

private:
  bool exit;

  Game *game;
  Keyboard *keyboard;
};

#endif // !APPLICATION_HPP
