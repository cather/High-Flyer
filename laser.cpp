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
  setX( rocket_->getWidth()/2 + rocket_->getX());
  setY( rocket_->getY() - rocket_->getHeight()+height_);
}

void Laser::shoot(int x, int y){
  findStartingPoint();
  int xdir = 1, ydir = 1;

  int xvel = 0, yvel = 0;
  xvel = (x - x_) / velocityX_;
  yvel = (y - y_) / velocityY_;
  
  cout << xvel << " " <<yvel<<endl;
  
  setVx( xdir * xvel );
  setVy( ydir * yvel );
  
  cout << velocityX_ << " " << velocityY_ <<endl;
  
  
  
}

