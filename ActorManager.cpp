#include <iostream>

#include "Actor.hpp"
#include "ActorManager.hpp"

using namespace std;

ActorManager::ActorManager() {}

void ActorManager::add(Actor *actor) {
  actors.push_back(actor);
}

void ActorManager::del(Actor *actor) {
  list<Actor *>::iterator tempActorsIter;

  tempActorsIter = find(actors.begin(), actors.end(), actor);
  if (tempActorsIter != actors.end()) {
    actors.erase(tempActorsIter);
  }
}

void ActorManager::rewind() {
  actorsIter = actors.begin();
}

Actor *ActorManager::next() {
  Actor *tempActor;
  if (actorsIter == actors.end()) {
    return nullptr;
  }
  tempActor = *actorsIter;
  actorsIter++;
  return tempActor;
}

Actor *ActorManager::current() {
  if (actorsIter == actors.end()) {
    return nullptr;
  } else {
    return *actorsIter;
  }
}

int ActorManager::size() const {
  return actors.size();
}

void ActorManager::update() {
  for (auto &actor : actors) {
    actor->update();
  }
}

ActorManager::~ActorManager() {
  for (auto actor : actors) {
    delete actor;
  }
}