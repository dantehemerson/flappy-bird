#pragma once
#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Game.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include <string>

class Application {
public:
  Application();

  void init(int argc, char **arv);

  void loop();

  Keyboard *getKeyboard() const;
  Mouse *getMouse() const;

  void quit();

  ~Application();

  typedef struct {
    int width;
    int height;
    int fps;
    int scale;
    string title;
  } Settings_t;

  Settings_t settings;

private:
  bool exit;

  Game *game;
  Keyboard *keyboard;
  Mouse *mouse;
};

#endif // !APPLICATION_HPP
