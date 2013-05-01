#ifndef PLANET_H
#define PLANET_H

#include "thing.h"
#include "rocket.h"

/** Planets are stationary objects that will appear to scroll down in the background of the game. When the rocket touches them, the rocket loses a life immediately. Planets cannot be destroyed. Velocity is always 0 in x direction and preset to 10 in y direction*/

class Planet : public Thing {
  public:
    Planet(QPixmap* pic, int x, int y, int w, int h);
    Planet();
    ~Planet();
    bool collidesWith(Thing* rocket);
  private:
};
#endif //PLANET_H
