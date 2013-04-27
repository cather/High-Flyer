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
  if (x < x_)
    xdir = -1;
  if (y < y_)
    ydir = -1;
    
  cout << "Clicking " << x << " " << y << endl;
  
  setVx( xdir * velocityX_ );
  setVy( ydir * velocityY_ );
  
  cout << "Moving " << velocityX_ << " " <<velocityX_ << endl;
  
}

