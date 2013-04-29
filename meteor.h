#ifndef METEOR_H
#define METEOR_H

#include "thing.h"
#include "rocket.h"
#include <math.h>

/* Meteor moves horizontally across the screen. Starting position is random position on left side of screen */

class Meteor : public Thing {
  public:
    Meteor(QPixmap* pic, int y, int vx );
    Meteor();
    ~Meteor();
    void die();
    bool collidesWith(Thing* enemy); // reacts when collides with rocket, laser
  private:
    bool hit;
};
#endif //METEOR_H

