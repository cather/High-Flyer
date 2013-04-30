#ifndef METEOR_H
#define METEOR_H

#include "thing.h"
#include "rocket.h"
#include <math.h>

/** Meteors moves horizontally across the screen. Starting position is random position on left side of screen */

class Meteor : public Thing {
  public:
    Meteor(QPixmap* pic, int y, int w, int h, int vx);
    Meteor();
    ~Meteor();
    bool collidesWith(Thing* enemy); // reacts when collides with rocket, laser
    void move(int windowMaxX, int windowMaxY);
};
#endif //METEOR_H

