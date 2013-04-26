#ifndef LASER_H
#define LASER_H

#include "thing.h"
#include "rocket.h"

/* Laser moves in direction from spaceship to mouse. Starting position is tip of the rocketship*/

class Laser : public Thing {
  public:
    Laser(QPixmap* pic, int w, int h, int vx, int vy, Rocket* rocket);
    Laser();
    ~Laser();
    void move(int x, int y);
    
  private:
    Rocket* rocket_;
};
#endif //LASER_H
