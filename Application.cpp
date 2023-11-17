#include <raylib.h>

#include "Application.hpp"
#include "Keyboard.hpp"
#include "Logger.h"
#include "R.hpp"
#include "Utils.hpp"

using namespace std;

Application::Application() : exit(false) {
  this->settings = {.width = WITH_SCALE(143) + 800,
                    .height = WITH_SCALE(255),
                    .fps = 60,
                    .scale = 4,
                    .title = "Flappy Bird"};
}

void Application::init(int argc, char **argv) {
  InitWindow(this->settings.width, this->settings.height, this->settings.title.c_str());
  SetTargetFPS(this->settings.fps);

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
