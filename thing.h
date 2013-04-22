#ifndef THING_H
#define THING_H

#include QGraphicsPixMapItem;

class Thing{
  public:
    Thing();
    ~Thing();
    virtual void move(int x, int y) = 0;
    virtual bool collide(Thing t) = 0;
  
  protected:
    int x;
    int y;
    int velocity;
    int health;
    QGraphicsPixMapItem pic;

}
#endif
