#include <iostream>
#include <string>
#include <vector>

#include "ActorManager.hpp"
#include "Application.hpp"
#include "Bird.hpp"
#include "Control.hpp"
#include "ControlManager.hpp"
#include "Game.hpp"
#include "Keyboard.hpp"
#include "Logger.h"
#include "Pipe.hpp"
#include "PipesManager.hpp"
#include "StageManager.hpp"
#include "Surface.hpp"
#include "Text.hpp"
#include "Utils.hpp"
#include <raylib.h>

using namespace std;

Game::Game(Application *const app)
    : Interface(app), controlManager(nullptr), actorManager(nullptr), stageManager(nullptr) {

  this->controlManager = new ControlManager();
  controlManager->addPeripheral(this->app->getKeyboard());

  this->actorManager = new ActorManager();
  this->stageManager = new StageManager(actorManager);

  PipesManager *pipesManager = new PipesManager();
  pipesManager->setVelocityX(-WITH_SCALE(1));
  this->actorManager->add(pipesManager);

  Bird *bird = new Bird(WITH_SCALE(143 / 2), 400, this);
  Control *controlBird = new Control();
  controlBird->setOwner(bird);

  controlBird->addActionName(BirdActions::BIRD_ACTION_JUMP, "Bird jump");
  controlBird->setActionPeripheral(BirdActions::BIRD_ACTION_JUMP, this->app->getKeyboard(),
                                   KeyboardKey::KEY_SPACE, Peripheral::ON_PRESS);

  controlManager->addControl(controlBird);
  actorManager->add(bird);

  Surface *surface = new Surface(this);
  this->actorManager->add(surface);

  Text *text = new Text(Utils::FONT_SIZE::LARGE, WITH_SCALE(143 / 2), 100);
  this->actorManager->add(text);

  text->setText(to_string(this->score));

  this->reinit();
}

void Game::draw() const {
  DrawTextureRec(R::getSingleton().getTexture(R::TextureIds::FLAPPY_SPRITES),
                 {0, 0, WITH_SCALE(143), WITH_SCALE(255)}, {0, 0}, WHITE);
}

void Game::update() {
  stageManager->update();
  controlManager->update();
  actorManager->update();

  DrawFPS(10, 10);
}

void Game::doAction(action_t action, int magnitute) {}

void Game::reinit() {
  this->score = 0;
};

void Game::over(){

};

Game::~Game() {
  delete this->controlManager;
  delete this->actorManager;
  delete this->stageManager;
}
