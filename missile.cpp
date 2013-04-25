#include "missile.h"

Missile::Missile(int x, int y, int speed, int lifeSpan, Rocket* rocketToChase ) : Thing(x, y, 0, 0, speed, 0, lifeSpan) {
  
  x_ = x;
  y_ = y;
  width_ = 10;
  height_ = 50;
  velocityX_ = speed;
  timeLimit = lifeSpan;
  rocket = rocketToChase;
  velocityX_ = ( rocket->getX() - x_ )/abs(( rocket->getX() - x_ )) * velocityX_;
  velocityY_ = ( rocket->getY() - y_ )/ abs(( rocket->getY() - y_ )) *velocityX_;
  
  QGraphicsPixmapItem* pic = new QGraphicsPixmapItem(QPixmap("images/missile.jpg"));
  setPic(pic);
  //since pic isn't working right now
  setBrush(Qt::yellow);
}

Missile::Missile(){
}

Missile::~Missile(){
}

void Missile::updateVelocity(){
  velocityX_ = ( rocket->getX() - x_ )/abs(( rocket->getX() - x_ )) * velocityX_;
  velocityY_ = ( rocket->getY() - y_ )/ abs(( rocket->getY() - y_ )) *velocityX_;
}
