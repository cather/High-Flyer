#ifndef MEGASTAR_H
#define MEGASTAR_H

#include "thing.h"
#include "rocket.h"
#include <math.h>

/** Megastars move to avoid rockets.*/

class Megastar : public Thing {
  public:
    Megastar(QPixmap* pic, int x, int y, int w, int h, int speed, Rocket* rocketToAvoid);
    Megastar();
    ~Megastar();
    void move(int windowMaxX, int windowMaxY);
    bool collidesWith(Thing* enemy);
    void explode();
  private:
    /** the rocket to avoid*/
    Rocket* rocket_;
    /** the speed of the Megastar */
    int speed_;
};
#endif //MEGASTAR_H
