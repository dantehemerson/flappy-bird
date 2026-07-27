#include <string>

#include "ActorManager.hpp"
#include "Application.hpp"
#include "Bird.hpp"
#include "Control.hpp"
#include "ControlManager.hpp"
#include "FinishScreen.hpp"
#include "Game.hpp"
#include "GetReadyScreen.hpp"
#include "Globals.hpp"
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
      surface(nullptr), getReadyScreen(nullptr) {
  this->score = 0;

  // Screens
  this->getReadyScreen = new GetReadyScreen();
  this->finishScreen = new FinishScreen(this);

  Control *controlFinishScreen = new Control();
  controlFinishScreen->setOwner(this->finishScreen);

  controlFinishScreen->addActionName(FinishScreen::Actions::PLAY_AGAIN, "Play again");
  controlFinishScreen->setActionPeripheral(FinishScreen::Actions::PLAY_AGAIN, this->app->getKeyboard(),
                                   KeyboardKey::KEY_SPACE, Peripheral::ON_PRESS);

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
  this->controlManager->addControl(controlFinishScreen);

  surface = new Surface(this);
  this->actorManager->add(surface);

  this->actorManager->add(bird);

  this->textScore = new Text(Utils::FONT_SIZE::LARGE, Globals::Settings::WIDTH / 2.0, 80);
  this->textScore->setText(to_string(this->score));

  this->actorManager->add(this->textScore);
  this->actorManager->add(this->getReadyScreen);
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

  DrawLine(0, Globals::Constants::SURFACE_Y, WITH_SCALE(143), Globals::Constants::SURFACE_Y, RED);
}

void Game::update() {
  this->stageManager->update();
  this->controlManager->update();
  this->actorManager->update();

  if (this->pipesManager->hasBirdCollided()) { // TODO: Improve conditional performance here:
    if (!this->bird->isDead())
      this->execute(Game::GameActions::BIRD_DIED);
  } else if (this->pipesManager->hasBirdPassedPipe()) {
    this->score++;
    this->textScore->setText(to_string(this->score));
  }

  DrawFPS(10, 10);
}

void Game::doAction(action_t action, int magnitute) {}

void Game::execute(GameActions action) {
  switch (action) {
    case GameActions::BIRD_STARTED_MOVING:
      this->getReadyScreen->setState(GetReadyScreen::State::HIDDING);
      this->pipesManager->setState(PipesManager::PipesState::MOVING);
      break;
    case GameActions::BIRD_DIED:
      this->pipesManager->setState(PipesManager::PipesState::STOPPED);
      this->surface->setState(Surface::SurfaceState::STOPPED);
      this->finishScreen->setState(FinishScreen::State::SHOW);
      this->bird->setState(Bird::BirdState::DEAD_WITH_FALL);
      break;

    case GameActions::PLAY_AGAIN:
      this->reinit();
      break;
    default:
      break;
  }
}

void Game::reinit() {
  this->score = 0;
  this->textScore->setText(to_string(this->score));
  this->bird->setState(Bird::BirdState::STATE_IDLE);
  this->bird->position = {WITH_SCALE(50), WITH_SCALE(126)};
  this->finishScreen->setState(FinishScreen::State::HIDDEN);
  this->getReadyScreen->setState(GetReadyScreen::State::SHOW);
  this->surface->setState(Surface::SurfaceState::MOVING);
  this->pipesManager->setState(PipesManager::PipesState::STOPPED);
  this->pipesManager->resetPipes();
};

void Game::over() {

};

Game::~Game() {
  delete this->getReadyScreen;
  delete this->controlManager;
  delete this->actorManager;
  delete this->stageManager;
}
