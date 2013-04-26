#ifndef METEOR_H
#define METEOR_H

#include "thing.h"
#include <math.h>

/* Meteor moves horizontally across the screen. Starting position is random position on left side of screen */

class Meteor : public Thing {
  public:
    Meteor(QPixmap* pic, int y, int vx, int maxHealth);
    Meteor();
    ~Meteor();
    void die();
    
  private:
    bool hit;
};
#endif //METEOR_H

