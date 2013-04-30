#ifndef MISSILE_H
#define MISSILE_H

#include "thing.h"
#include "rocket.h"
#include <math.h>

/* Missile follows rocket ship. Starting position is Alien*/

class Missile : public Thing {
  public:
    Missile(QPixmap* pic, int x, int y, int w, int h, int speed, Rocket* rocketToChase, QPixmap* explosion );
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
    int time;
    int explosionCounter;
    QPixmap* explosion_;
};
#endif //MISSILE_H
