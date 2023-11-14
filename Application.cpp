#include <raylib.h>

#include "Application.hpp"
#include "Keyboard.hpp"
#include "Logger.h"
#include "R.hpp"
#include "Utils.hpp"

using namespace std;

Application::Application() : exit(false) {}

void Application::init(int argc, char **argv) {
  InitWindow(WITH_SCALE(143), WITH_SCALE(255), "Bird");
  SetTargetFPS(60);

  R::getSingleton().loadResources();

  this->keyboard = new Keyboard();
  this->game = new Game(this);
}

void Application::loop() {
  while (!this->exit && !WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    this->game->draw();
    this->game->update();

    EndDrawing();
  }
}

Keyboard *Application::getKeyboard() const {
  return this->keyboard;
}

void Application::quit() {
  this->exit = true;
}

Application::~Application() {
  CloseWindow();
}
