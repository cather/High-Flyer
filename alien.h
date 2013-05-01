#ifndef ALIEN_H
#define ALIEN_H

#include "thing.h"
#include "missile.h"
/** The Alien class appears from a random position above the screen, and has a velocity that makes it move around randomly on the screen for a certain time. After that time is up, it moves in constant velocity until exiting the screen. */
class Alien : public Thing {
  public:
    Alien(QPixmap* pix, int w, int h, int rf);
    Alien();
    ~Alien();
    void move(int windowMaxX, int windowMaxY);    
    bool collidesWith(Thing* rocket);
    
  private:
    /** Counter that decrements every time the Alien is moved to indicate how many times the Alien will set its velocity randomly.*/
    int lifeTime_;
    /** The number by which the Alien's velocity and intial x-position will be modulo'd by to produce random values*/
    int randFactor_;
  
};
#endif //ALIEN_H
