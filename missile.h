#ifndef MISSILE_H
#define MISSILE_H

#include "thing.h"

/* Missile follows rocket ship. Starting position is Alien*/

class Missile : public Thing {
  public:
    Missile();
    ~Missile();
    void move(int x, int y);
    
  private:
};
#endif //MISSILE_H
