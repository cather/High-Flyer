#ifndef METEOR_H
#define METEOR_H

#include "thing.h"
#include <math.h>

/* Meteor moves horizontally across the screen. Starting position is random position on left side of screen */

class Meteor : public Thing {
  public:
    Meteor();
    ~Meteor();
    void move();
    
  private:
};
#endif //METEOR_H

