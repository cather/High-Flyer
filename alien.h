#ifndef ALIEN_H
#define ALIEN_H

#include "thing.h"
#include "missile.h"
/** The Alien class appears from a random direction on the screen, and has a random velocity that makes it move around randomly on the screen. */

class Alien : public Thing {
  public:
    Alien(QPixmap* pix, int w, int h, int rf);
    Alien();
    ~Alien();
    void move(int windowMaxX, int windowMaxY);    
    bool collidesWith(Thing* rocket);
    
  private:
    /** Counter that decrements every time the Alien is moved. When the counter = 0, the Alien leaves the screen and dies.*/
    int lifeTime_;
    /** The number by which the Alien's velocity will be modulo'd by to produce a random velocity*/
    int randFactor_;
  
};
#endif //ALIEN_H
