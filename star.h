#ifndef STAR_H
#define STAR_H


class Star : public Thing {
  public:
    Star();
    ~Star();
    void move(int x, int y);
    bool collide(Thing t);
  
  private:
}
#endif
