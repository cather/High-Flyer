#ifndef PLANET_H
#define PLANET_H


class Planet : public Thing {
  public:
    Planet();
    ~Planet();
    void move(int x, int y);
    bool collide(Thing t);
  
  private:
}
#endif
