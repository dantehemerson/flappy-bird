#include <iostream>
#include <vector>

#include "ActorManager.hpp"
#include "Application.hpp"
#include "Bird.hpp"
#include "Control.hpp"
#include "ControlManager.hpp"
#include "Game.hpp"
#include "Keyboard.hpp"
#include "Logger.h"
#include "StageManager.hpp"
#include "Utils.hpp"
#include <raylib.h>

using namespace std;

Game::Game(Application *const app)
    : Interface(app), controlManager(nullptr), actorManager(nullptr), stageManager(nullptr) {

  this->controlManager = new ControlManager();
  controlManager->addPeripheral(this->app->getKeyboard());

  this->actorManager = new ActorManager();
  this->stageManager = new StageManager(actorManager);

  Bird *bird = new Bird(this->app->settings.width / 2 - 30, 400, this);
  Control *controlBird = new Control();
  controlBird->setOwner(bird);

  controlBird->addActionName(BirdActions::BIRD_ACTION_JUMP, "Bird jump");
  controlBird->setActionPeripheral(BirdActions::BIRD_ACTION_JUMP, this->app->getKeyboard(),
                                   KeyboardKey::KEY_SPACE, Peripheral::ON_PRESS);

  controlManager->addControl(controlBird);
  actorManager->add(bird);
}

void Game::draw() const {
  DrawTextureRec(R::getSingleton().getTexture(R::TextureIds::FLAPPY_SPRITES),
                 {0, 0, WITH_SCALE(143), WITH_SCALE(255)}, {0, 0}, WHITE);
}

void Game::update() {
  stageManager->update();
  controlManager->update();
  actorManager->update();
}

void Game::doAction(action_t action, int magnitute) {}

void Game::reinit(){};

void Game::over(){};

Game::~Game() {
  delete this->controlManager;
  delete this->actorManager;
  delete this->stageManager;
}
