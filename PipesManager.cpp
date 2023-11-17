#include <algorithm>

#include "Logger.h"
#include "Pipe.hpp"
#include "PipesManager.hpp"
#include "Utils.hpp"
#include <raylib.h>

using namespace std;

PipesManager::PipesManager() {
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
  this->pipes[0]->position.x = WITH_SCALE(100);

  for (size_t i = 1; i < this->pipes.size(); i++) {
    this->pipes[i]->position.x = this->pipes[i - 1]->position.x + this->distanceBetweenPipes;
    this->pipes[i]->position.y = Utils::randomFloat(WITH_SCALE(-160), 0);
  }
}

void PipesManager::update() {
  for (size_t i = 0; i < this->pipes.size(); i++) {
    this->pipes[i]->position.x += this->velocityX;

    LogError << "y: " << this->pipes[i]->position.y << std::endl;

    bool outOfScreen = this->pipes[i]->position.x < -WITH_SCALE(30);
    if (outOfScreen) {
      size_t previousPipeIdx = i == 0 ? this->pipes.size() - 1 : i - 1;
      this->pipes[i]->position.x =
          this->pipes[previousPipeIdx]->position.x + this->distanceBetweenPipes;
      this->pipes[i]->position.y = Utils::randomFloat(WITH_SCALE(-160), 0);
    }
  }
}

void PipesManager::setVelocityX(const float &velocity) {
  this->velocityX = velocity;
}
