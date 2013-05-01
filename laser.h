#ifndef LASER_H
#define LASER_H

#include "thing.h"
#include "rocket.h"

/** A Laser Thing that moves in the direction from the rocket to a given point. Starting position is tip of the rocket*/

class Laser : public Thing {
  public:
    Laser(QPixmap* pic, int w, int h, int vx, int vy, Rocket* rocket);
    Laser();
    ~Laser();
    void shoot (int x, int y);
    
    bool collidesWith(Thing* enemy);

};
#endif //LASER_H
