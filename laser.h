#ifndef LASER_H
#define LASER_H

#include "thing.h"
#include "rocket.h"

/* Laser moves in direction from spaceship to mouse. Starting position is tip of the rocketship*/

class Laser : public Thing {
  public:
    Laser(QPixmap* pic, int vx, int vy, Rocket* rocket);
    Laser();
    ~Laser();
    void findStartingPoint();
    
  private:
    Rocket* rocket_;
    
  public slots:
    void  shootLaser(int,int);
};
#endif //LASER_H
