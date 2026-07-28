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
#include "HiddenText.hpp"
#include "Interface.hpp"
#include "Peripheral.hpp"
#include "Pipe.hpp"
#include "PipesManager.hpp"
#include "R.hpp"
#include "StageManager.hpp"
#include "Surface.hpp"
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

  controlFinishScreen->addActionPeripheral(FinishScreen::Actions::PLAY_AGAIN,
                                           this->app->getKeyboard(), KeyboardKey::KEY_SPACE,
                                           Peripheral::ON_PRESS);
  controlFinishScreen->addActionPeripheral(FinishScreen::Actions::PLAY_AGAIN,
                                           this->app->getMouse(), MouseButton::MOUSE_BUTTON_LEFT,
                                           Peripheral::ON_PRESS);

  this->controlManager = new ControlManager();
  controlManager->addPeripheral(this->app->getKeyboard());
  controlManager->addPeripheral(this->app->getMouse());

  this->actorManager = new ActorManager();
  this->stageManager = new StageManager(actorManager);

  this->bird = new Bird(WITH_SCALE(50), WITH_SCALE(126), this);
  this->bird->setState(Bird::BirdState::STATE_IDLE);

  Control *controlBird = new Control();
  controlBird->setOwner(bird);

  controlBird->addActionPeripheral(BirdActions::BIRD_ACTION_JUMP, this->app->getKeyboard(),
                                   KeyboardKey::KEY_SPACE, Peripheral::ON_PRESS);
  controlBird->addActionPeripheral(BirdActions::BIRD_ACTION_JUMP, this->app->getMouse(),
                                   MouseButton::MOUSE_BUTTON_LEFT, Peripheral::ON_PRESS);

  this->pipesManager = new PipesManager(this->bird);
  pipesManager->setVelocityX(-WITH_SCALE(1));

  this->actorManager->add(pipesManager);

  this->controlManager->addControl(controlBird);
  this->controlManager->addControl(controlFinishScreen);

  surface = new Surface(this);
  this->actorManager->add(surface);

  this->actorManager->add(bird);

  this->textScore = new HiddenText(Utils::FONT_SIZE::LARGE, Globals::Settings::WIDTH / 2.0, 80);
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
}

void Game::update() {
  this->stageManager->update();
  this->controlManager->update();
  this->actorManager->update();

  if (!this->bird->isDead()) {
    if (this->pipesManager->hasBirdCollided()) {
      this->bird->setState(Bird::BirdState::DEAD_WITH_FALL);
      this->execute(GameActions::BIRD_DIED);
    } else if (this->pipesManager->hasBirdPassedPipe()) {
      this->score++;
      this->textScore->setText(to_string(this->score));
      PlaySound(R::getSingleton().getSound(R::SoundId::POINT));
    }
  }

#ifdef DEBUG_BUILD
  DrawFPS(10, 10);
#endif
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
      this->finishScreen->setScore(this->score);
      this->finishScreen->setBestScore(9999);
      this->finishScreen->setState(FinishScreen::State::START_SHOWING);
      this->textScore->hide();
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
  this->textScore->show();
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
  delete this->controlManager;
  delete this->actorManager;
  delete this->stageManager;
}
