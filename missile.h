#ifndef MISSILE_H
#define MISSILE_H

#include "thing.h"
#include "rocket.h"
#include <math.h>

/** Missile follows rocket ship. Dies after a certain amount of time. Starting position is Alien*/

class Missile : public Thing {
  public:
    Missile(QPixmap* pic, int x, int y, int w, int h, int speed, Rocket* rocketToChase);
    Missile();
    ~Missile();
    void move(int windowMaxX, int windowMaxY);
    bool collidesWith(Thing* enemy);
    void explode();
  private:
    /** the rocket being followed*/
    Rocket* rocket_;
    /** the speed of the missile */
    int speed_;
    /** counter for how many time the missile can move before dying*/
    int explosionCounter;
    /** counter for how often missile should recalculate its velocity to chase the rocket*/
    int recalculateCounter;
};
#endif //MISSILE_H
