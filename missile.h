#ifndef MISSILE_H
#define MISSILE_H


class Missile : public Thing {
  public:
    Missile();
    ~Missile();
    void move(int x, int y);
    bool collide(Thing t);
  
  private:
}
#endif
