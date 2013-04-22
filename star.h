#ifndef STAR_H
#define STAR_H

#include "thing.h"

/*Stars don't move. Appear in random spot in 'background' of game*/

class Star : public Thing {
  public:
    Star();
    ~Star();
  
  private:
  
  signals:
    void collected();
};
#endif //STAR_H
