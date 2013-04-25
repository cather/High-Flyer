#ifndef MISSILE_H
#define MISSILE_H

#include "thing.h"
#include "rocket.h"
#include <math.h>

/* Missile follows rocket ship. Starting position is Alien*/

class Missile : public Thing {
  public:
    Missile(int x, int y, int speed, int lifeSpan, Rocket* rocket );
    Missile();
    ~Missile();
    void updateVelocity();
    
  private:
    int timeLimit;
    Rocket* rocket;
};
#endif //MISSILE_H
