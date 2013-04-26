#ifndef ALIEN_H
#define ALIEN_H

#include "thing.h"
/* Alien moves around on the screen randomly. Starting position is random direction off-screen*/

class Alien : public Thing {
  public:
    Alien(QPixmap* pix, int rf, int onScreenFor);
    Alien();
    ~Alien();
    void move(int windowMaxX, int windowMaxY);
    int lifeTime_; // indicates how long Alien will move around on the screen
    int hoverTime_;
    int randFactor_; // random number that decides how much alien will move
    
  private:
  
  signals:
    void attack(); // signal to drop a missile
  
};
#endif //ALIEN_H
