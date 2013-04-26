#ifndef MISSILE_H
#define MISSILE_H

#include "thing.h"
#include "rocket.h"
#include <math.h>

/* Missile follows rocket ship. Starting position is Alien*/

class Missile : public Thing {
  public:
    Missile(QPixmap* pic, int x, int y, int speed, int lifeSpan, Rocket* rocket );
    Missile();
    ~Missile();
    void updateVelocity();
  private:
    Rocket* rocket;
    int speed_;
};
#endif //MISSILE_H
