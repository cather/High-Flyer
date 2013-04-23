#include "rocket.h"

Rocket::Rocket(double nx, double ny, double w, double h, int vx, int vy, int maxHealth ) : Thing(nx, ny, w, h, vx, vy, maxHealth) {
  x_ = nx;
  y_ = ny;
  width_ = w;
  height_ = h;
  health_ = maxHealth;
  velocityX_ = vx;
  velocityY_ = vy;
  QGraphicsPixmapItem* pic = new QGraphicsPixmapItem(QPixmap("images/rocket.jpg"));
  setPic(pic);
}

Rocket::Rocket(){
}


Rocket::~Rocket(){
}

