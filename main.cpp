#include <iostream>
#include <raylib.h>

#include "Application.hpp"
#include "Logger.h"

using namespace std;

int main() {

  Application app;

  app.init(0, nullptr);

  app.loop();

  app.quit();

  return 0;
}