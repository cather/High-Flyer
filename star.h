#ifndef STAR_H
#define STAR_H

#include "thing.h"
#include "rocket.h"

/*Stars don't move. Appear in random spot in 'background' of game*/

class Star : public Thing {
  public:

    Star(QPixmap* pic, int x, int y);
    Star();
    ~Star();
    void collide(Thing* thing);
    void addPoints(Rocket* rocket);
    
  private:
  
  signals:
};
#endif //STAR_H
