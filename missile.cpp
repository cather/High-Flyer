#include "missile.h"

Missile::Missile(int x, int y, int speed, int lifeSpan, Rocket* rocketToChase ) : Thing(x, y, 0, 0, speed, 0, lifeSpan) {
  
  x_ = x;
  y_ = y;
  width_ = 100;
  height_ = 500;
  health_ = lifeSpan;
  rocket = rocketToChase;
  speed_ = speed;
  velocityX_ = ( rocket->getX() - x_ )/abs(( rocket->getX() - x_ )) * speed_;
  velocityY_ = ( rocket->getY() - y_ )/ abs(( rocket->getY() - y_ )) * speed_;
  
  QGraphicsPixmapItem* pic = new QGraphicsPixmapItem(QPixmap("images/missile.jpg"));
  setPic(pic);
  //since pic isn't working right now
  setBrush(Qt::yellow);
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
