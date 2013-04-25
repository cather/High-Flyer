#include "meteor.h"

Meteor::Meteor(int y, double w, double h, int vx, int maxHealth ): Thing(0, y, w, h, vx, 0, maxHealth) {
  x_ = 0;
  y_ = y;
  width_ = w;
  height_ = h;
  health_ = maxHealth;
  velocityX_ = vx;
  velocityY_ = 0;
  hit = false;
  
  QGraphicsPixmapItem* pic = new QGraphicsPixmapItem(QPixmap("images/meteor.jpg"));
  setPic(pic);
  //since pic isn't working right now
  setBrush(Qt::blue);
}

Meteor::Meteor(){
  x_ = 0;
  y_ = rand()%10;
  width_ = 10;
  height_ = 10;
  health_ = 20;
  velocityX_ = 5;
  velocityY_ = 0;
}

Meteor::~Meteor(){
}

void Meteor::die(){
  delete this;
}
