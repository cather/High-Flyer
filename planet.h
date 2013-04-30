#ifndef PLANET_H
#define PLANET_H

#include "thing.h"
#include "rocket.h"

/** Planets are stationary objects that will appear in the scrolling background of the game. When the rocket touches them, the rocket loses a life immediately. Planets cannot be destroyed*/

class Planet : public Thing {
  public:
    /** Constructor
        @param pix the QPixmap to represent the planet
        @param x the planet's x coord
        @param y the planet's y cood
        x and y velocities are set to 0. maxhealth is set to 100, an arbitrary number that will always be reset so the planet's current health never reaches 0. `
    */
    Planet(QPixmap* pic, int x, int y, int w, int h);
    /** Constructor*/
    Planet();
    /** Destructpr*/
    ~Planet();
    bool collidesWith(Thing* rocket);
  private:
};
#endif //PLANET_H
