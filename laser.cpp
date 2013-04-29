#include "laser.h"
using namespace std;
Laser::Laser(QPixmap* pic, int vx, int vy, Rocket* rocket ) : Thing(pic, rocket->getWidth()/2+rocket->getX(), rocket->getY(), vx, vy, 1 ){

  rocket_ = rocket;
  identifier = "laser";
}


Laser::Laser(){
}

Laser::~Laser(){
}

void Laser::findStartingPoint(){
}

void Laser::shoot(int x, int y){
  findStartingPoint();
  int xvel = 0, yvel = 0;
  xvel = (x - x_) / velocityX_;
  yvel = (y - y_) / velocityY_;
  
  setVx( xvel );
  setVy( yvel );
}


bool Laser::collidesWith(Thing* enemy){

  if (collidesWithItem(enemy, Qt::IntersectsItemShape))
    enemy->decrementHealth(1); // hurt enemy
  return collidesWithItem(enemy, Qt::IntersectsItemShape);
}
