#pragma once
#ifndef ACTORMANAGER_HPP
#define ACTORMANAGER_HPP

#include <list>

class Actor;

class ActorManager {
public:
  ActorManager();

  void add(Actor *actor);
  void del(Actor *actor);
  void rewind();
  Actor *next();
  Actor *current();
  void update();
  int size() const;

  ~ActorManager();

private:
  std::list<Actor *> actors;
  std::list<Actor *>::iterator actorsIter;
};

#endif // !ACTORMANAGER_HPP
