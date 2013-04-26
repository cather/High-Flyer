#include "laser.h"
using namespace std;
Laser::Laser(QPixmap* pic, int vx, int vy, Rocket* rocket ) : Thing(pic, rocket->getWidth()/2, rocket->getY(), vx, vy, 1 ){

  rocket_ = rocket;
}


Laser::Laser(){
}

Laser::~Laser(){
}

void Laser::findStartingPoint(){
  setX( rocket_->getWidth()/2 );
  setY( rocket_->getY() );
}

void Laser::shootLaser(int x, int y){
  cout << "ds"<<endl;
  findStartingPoint();
  setVx(x);
  setVy(y);
  
  move();
}
