#ifndef ALIEN_H
#define ALIEN_H

#include "thing.h"
/* Alien moves around on the screen randomly. Starting position is random direction off-screen*/

class Alien : public Thing {
  public:
    Alien();
    ~Alien();
    void move(int x, int y);
    
  private:
  
  signals:
    void attack(); // signal to drop a missile
  
};
#endif //ALIEN_H
