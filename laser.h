#ifndef LASER_H
#define LASER_H

class Laser : public Thing {
  public:
    Laser();
    ~Laser();
    void move(int x, int y);
    
  private:
};
#endif //LASER_H
