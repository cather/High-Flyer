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
    void move(int windowMaxX, int windowMaxY);
  private:
    Rocket* rocket;
    int speed_;
    bool firstMove;
    bool down;
};
#endif //MISSILE_H
