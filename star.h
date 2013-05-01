#ifndef STAR_H
#define STAR_H

#include "thing.h"
#include "rocket.h"

/** Stars have a pic, x, y, width, and height. They appear randomly above the screen and move down in a twitchy pattern. They disappear when their collidesWith function returns true*/

class Star : public Thing {
  public:
    Star(QPixmap* pic, int x, int y, int w, int h);
    Star();
    ~Star();
    bool collidesWith(Thing* rocket);
    void move(int windowMaxX, int windowMaxY);
  private:
    /** true on the first time the move function is called*/
    bool firstMove;
    /** true every other time the move function is called*/
    bool down;
};
#endif //STAR_H
