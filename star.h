#ifndef STAR_H
#define STAR_H

#include "thing.h"
#include "rocket.h"

/** Stars have a pic, x, y, width, and height. They appear in random spot in 'background' of game and don't move. They disappear when their collidesWith function returns true*/

class Star : public Thing {
  public:
    Star(QPixmap* pic, int x, int y, int w, int h);
    Star();
    ~Star();
    bool collidesWith(Thing* rocket);
};
#endif //STAR_H
