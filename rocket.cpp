#include "rocket.h"
#include <QBrush>

#define speed 5

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
  
  //since pic isn't working right now
  setBrush(Qt::red);
}

Rocket::Rocket(){
}


Rocket::~Rocket(){
}

void Rocket::keyPressEvent(QKeyEvent* e)
{
  switch(e->key())
  {
    case Qt::Key_Up:
      setVx(0);
      setVy(speed);
      move();
      break;
    case Qt::Key_Left:
      setVx(-speed);
      setVy(0);
      move();
      break;
    case Qt::Key_Right:
      setVx(speed);
      setVy(0);
      move();
      break;
    case Qt::Key_Down:
      setVx(0);
      setVy(-speed);
      move();
      break;
  }
  
}
