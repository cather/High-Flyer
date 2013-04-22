#ifndef ROCKET_H
#define ROCKET_H

class Rocket : public Thing {
  public:
    Rocket();
    ~Rocket();
    void move(int x, int y): move(x,y);
    bool collide(Thing t);

  protected:
}
#endif


