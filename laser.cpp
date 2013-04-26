#include "laser.h"

Laser::Laser(QPixmap* pic, int w, int h, int vx, int vy, Rocket* rocket ) : Thing(pic, rocket->getWidth()/2, rocket->getY(), w, h, vx, vy, 1 ){

  rocket_ = rocket;
}


Laser::Laser(){
}

Laser::~Laser(){
}
