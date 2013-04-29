#ifndef MISSILE_H
#define MISSILE_H

#include "thing.h"
#include "rocket.h"
#include <math.h>

/* Missile follows rocket ship. Starting position is Alien*/

class Missile : public Thing {
  public:
    Missile(QPixmap* pic, int x, int y, int speed, int lifeSpan, Rocket* rocket, QPixmap* explosion);
    Missile();
    ~Missile();
    void move(int windowMaxX, int windowMaxY);
    bool collideWith(Thing* enemy); // enemies are planet, meteor, alien, laser, rocket
    void explode();
  private:
    Rocket* rocket_;
    int speed_;
    bool firstMove;
    bool down;
    int explosionCounter;
    QPixmap* explosion_;
};
#endif //MISSILE_H
