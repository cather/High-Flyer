#ifndef METEOR_H
#define METEOR_H


class Meteor : public Thing {
  public:
    Laser();
    ~Laser();
    void move(int x, int y);
    bool collide(Thing t);
  
  private:
}
#endif
