#ifndef PLANET_H
#define PLANET_H

#include "thing.h"

/*Planets don't move. Appear in random spot in 'background' of game*/

class Planet : public Thing {
  public:
    Planet();
    ~Planet();
    
  private:
};
#endif //PLANET_H
