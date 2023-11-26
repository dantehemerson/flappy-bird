#include <iostream>
#include <string>
#include <vector>

#include "ActorManager.hpp"
#include "Application.hpp"
#include "Bird.hpp"
#include "Control.hpp"
#include "ControlManager.hpp"
#include "FinishScreen.hpp"
#include "Game.hpp"
#include "GetReadyScreen.hpp"
#include "Globals.hpp"
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
    : Interface(app), controlManager(nullptr), actorManager(nullptr), stageManager(nullptr),
      getReadyScreen(nullptr) {
  this->score = 0;

  // Screens
  this->getReadyScreen = new GetReadyScreen();
  this->finishScreen = new FinishScreen(this);

  this->controlManager = new ControlManager();
  controlManager->addPeripheral(this->app->getKeyboard());

  this->actorManager = new ActorManager();
  this->stageManager = new StageManager(actorManager);

  this->bird = new Bird(WITH_SCALE(50), WITH_SCALE(126), this);
  this->bird->setState(Bird::BirdState::STATE_IDLE);

  Control *controlBird = new Control();
  controlBird->setOwner(bird);

  controlBird->addActionName(BirdActions::BIRD_ACTION_JUMP, "Bird jump");
  controlBird->setActionPeripheral(BirdActions::BIRD_ACTION_JUMP, this->app->getKeyboard(),
                                   KeyboardKey::KEY_SPACE, Peripheral::ON_PRESS);

  this->pipesManager = new PipesManager(this->bird);
  pipesManager->setVelocityX(-WITH_SCALE(1));

  this->actorManager->add(pipesManager);
  this->controlManager->addControl(controlBird);
  this->actorManager->add(bird);

  Surface *surface = new Surface(this);
  this->actorManager->add(surface);

  this->textScore = new Text(Utils::FONT_SIZE::LARGE, Globals::Settings::WIDTH / 2, 80);
  this->textScore->setText(to_string(this->score));

  this->actorManager->add(this->textScore);
  this->actorManager->add(this->finishScreen);

  this->reinit();
}

void Game::draw() const {
  // Background:
  DrawTextureRec(R::getSingleton().getTexture(R::TextureIds::FLAPPY_SPRITES),
                 {0, 0, WITH_SCALE(143), WITH_SCALE(255)}, {0, 0}, WHITE);
  DrawTextureRec(R::getSingleton().getTexture(R::TextureIds::FLAPPY_SPRITES),
                 {WITH_SCALE(0), 0, WITH_SCALE(143), WITH_SCALE(255)}, {WITH_SCALE(143), 0},
                 WHITE);
}

void Game::update() {
  this->stageManager->update();
  this->controlManager->update();
  this->actorManager->update();
  this->getReadyScreen->update();

  if (this->pipesManager->hasBirdCollided()) {
  } else if (this->pipesManager->hasBirdPassedPipe()) {
    this->score++;
    this->textScore->setText(to_string(this->score));
  }

  this->getReadyScreen->draw();

  DrawFPS(10, 10);
}

void Game::doAction(action_t action, int magnitute) {}

void Game::execute(GameActions action) {

  switch (action) {
    case GameActions::HIDE_GET_READY_SCREEN:
      this->getReadyScreen->setState(GetReadyScreen::State::HIDDING);
      break;

    default:
      break;
  }
}

void Game::reinit() {
  this->score = 0;
  this->textScore->setText(to_string(this->score));
};

void Game::over(){

};

Game::~Game() {
  delete this->getReadyScreen;
  delete this->controlManager;
  delete this->actorManager;
  delete this->stageManager;
}
