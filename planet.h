#ifndef PLANET_H
#define PLANET_H

#include "thing.h"
#include "rocket.h"

/*Planets don't move. Appear in random spot in 'background' of game*/

class Planet : public Thing {
  public:
    Planet(int x, int y, double w, double h);
    Planet();
    ~Planet();
    void collide(Rocket* rocket);
  private:
};
#endif //PLANET_H
