#include <raylib.h>

#include "Application.hpp"
#include "Globals.hpp"
#include "Keyboard.hpp"
#include "Logger.h"
#include "R.hpp"
#include "Utils.hpp"

using namespace std;

Application::Application() : exit(false) {
  this->settings = {.width = Globals::Settings::WIDTH,
                    .height = Globals::Settings::HEIGHT,
                    .fps = 60,
                    .scale = 4,
                    .title = "Flappy Bird"};
}

void Application::init(int argc, char **argv) {
  InitWindow(this->settings.width, this->settings.height, this->settings.title.c_str());
  InitAudioDevice();
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
  CloseAudioDevice();
  CloseWindow();
}
