#ifndef ROCKET_H
#define ROCKET_H

#include "thing.h"

/* Rocket movement will be controlled by arrow keys. Starting position is center bottom of screen */

class Rocket : public Thing {
  public:
  
    Rocket(double nx, double ny, double w, double h, int vx, int vy, int maxHealth );
    Rocket();
    ~Rocket();

  private:
};
#endif //ROCKET_H
