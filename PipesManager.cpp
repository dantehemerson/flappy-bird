#include "Bird.hpp"
#include "Pipe.hpp"
#include "PipesManager.hpp"
#include "Utils.hpp"
#include <raylib.h>

using namespace std;

PipesManager::PipesManager(Bird *bird) {
  this->bird = bird;
  this->pipes.push_back(new Pipe());
  this->pipes.push_back(new Pipe());
  this->pipes.push_back(new Pipe());
  this->pipes.push_back(new Pipe());

  this->resetPipes();
}

void PipesManager::draw() const {
  for (auto &pipe : this->pipes) {
    pipe->draw();
  }
}

void PipesManager::resetPipes() {
  this->distanceBetweenPipes = WITH_SCALE(90);
  // First pipe start at:
  this->pipes[0]->position.x = WITH_SCALE(240);
  this->pipes[0]->position.y = Utils::randomFloat(WITH_SCALE(-160), 0);

  for (size_t i = 1; i < this->pipes.size(); i++) {
    this->pipes[i]->position.x = this->pipes[i - 1]->position.x + this->distanceBetweenPipes;
    this->pipes[i]->position.y = Utils::randomFloat(WITH_SCALE(-160), 0);
  }

  this->state = PipesState::STOPPED;
}

void PipesManager::update() {
  if (this->state == PipesState::STOPPED) {
    return;
  }

  for (size_t i = 0; i < this->pipes.size(); i++) {
    this->pipes[i]->position.x += this->velocityX;

    bool outOfScreen = this->pipes[i]->position.x < -WITH_SCALE(30);
    if (outOfScreen) {
      size_t previousPipeIdx = i == 0 ? this->pipes.size() - 1 : i - 1;
      this->pipes[i]->position.x =
          this->pipes[previousPipeIdx]->position.x + this->distanceBetweenPipes;
      this->pipes[i]->position.y = Utils::randomFloat(WITH_SCALE(-160), 0);
      this->pipes[i]->setHasPassedBird(false);
    }
  }
}

void PipesManager::setVelocityX(const float &velocity) {
  this->velocityX = velocity;
}

void PipesManager::setState(PipesState state) {
  this->state = state;
}

bool PipesManager::hasBirdPassedPipe() {
  for (auto &pipe : this->pipes) {
    if (this->bird->position.x > pipe->position.x + (pipe->getWidth() / 2) &&
        !pipe->hasPassedBird()) {
      pipe->setHasPassedBird(true);
      return true;
    }
  }

  return false;
}

bool PipesManager::hasBirdCollided() const {
  for (auto &pipe : this->pipes) {
    bool collided = pipe->hasCollided(this->bird);
    // LogInfo << "Collided: " << collided << endl;
    if (collided) {


      return true;
    }
  }
  return false;
}
