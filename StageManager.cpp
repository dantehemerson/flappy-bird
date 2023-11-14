#include "StageManager.hpp"
#include "Actor.hpp"
#include "ActorManager.hpp"

StageManager::StageManager(ActorManager *_actorManager)
    : actorManager(_actorManager) {}

void StageManager::update() {
  this->draw();
}

void StageManager::draw() {
  this->actorManager->rewind();

  Actor *actor;
  while ((actor = this->actorManager->next()) != NULL) {
    actor->draw();
  }
}

StageManager::~StageManager() {}