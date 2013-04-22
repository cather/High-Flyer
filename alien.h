#ifndef ALIEN_H
#define ALIEN_H

class Alien : public Thing {
  public:
    Alien();
    ~Alien();
    void move(int x, int y);
    void attack(); // drop a missile
  
  private:
};
#endif //ALIEN_H
