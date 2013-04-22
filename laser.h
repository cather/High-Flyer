#ifndef LASER_H
#define LASER_H

#include "thing.h" 

/* Laser moves in direction from spaceship to mouse. Starting position is tip of the rocketship*/

class Laser : public Thing {
  public:
    Laser();
    ~Laser();
    void move(int x, int y);
    
  private:
};
#endif //LASER_H
