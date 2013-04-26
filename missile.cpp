#include "missile.h"

Missile::Missile(QPixmap* pic, int x, int y, int speed, int lifeSpan, Rocket* rocketToChase ) : Thing(pic, x, y,
  ( rocket->getX() - x_ )/abs(( rocket->getX() - x_ )), 
  ( rocket->getY() - y_ )/ abs(( rocket->getY() - y_ )), lifeSpan) {
 
  rocket = rocketToChase;
  speed_ = speed;
}

Missile::Missile(){
}

Missile::~Missile(){
}

// this should be checked at every clock
void Missile::updateVelocity(){
  velocityX_ = ( rocket->getX() - x_ )/abs(( rocket->getX() - x_ )) * speed_;
  velocityY_ = ( rocket->getY() - y_ )/ abs(( rocket->getY() - y_ )) * speed_;
}
