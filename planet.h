#ifndef PLANET_H
#define PLANET_H

#include "thing.h"
#include "rocket.h"

/*Planets don't move. Appear in random spot in 'background' of game*/

class Planet : public Thing {
  public:
    Planet(QPixmap* pic, int x, int y);
    Planet();
    ~Planet();
    bool collidesWith(Thing* rocket);
  private:
};
#endif //PLANET_H
