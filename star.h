#ifndef STAR_H
#define STAR_H

#include "thing.h"
#include "rocket.h"

/** Stars that appear in random spot in 'background' of game and don't move*/

class Star : public Thing {
  public:

    Star(QPixmap* pic, int x, int y, int w, int h);
    Star();
    ~Star();
    bool collidesWith(Thing* rocket);
    
  private:
  
  signals:
    void collected();
};
#endif //STAR_H
