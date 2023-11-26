#ifndef GET_READY_SCREEN_HPP
#define GET_READY_SCREEN_HPP

#include "Interface.hpp"

class GetReadyScreen {
public:
  GetReadyScreen();
  void draw() const;
  void update();

  enum class State { SHOW = 1, HIDDING, HIDDEN };

  void setState(State state);

private:
  State state;
  float opacity;
};

#endif // !GET_READY_SCREEN_HPP
