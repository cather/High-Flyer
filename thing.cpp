#include "thing.h"

// Thing(startX, startY, width, height, velX, velY, maxHealth)
Thing::Thing(double nx, double ny, double w, double h, int vx, int vy, int maxHealth ) : QGraphicsRectItem(nx, ny, w, h) {
  x_ = nx;
  y_ = ny;
  width_ = w;
  height_ = h;
  health_ = maxHealth;
  velocityX_ = vx;
  velocityY_ = vy;
}

Thing::Thing(){
}

Thing::~Thing(){
}

int Thing::getX(){
  return x_;
}

int Thing::getY(){
  return y_;
}

void Thing::setX(int x){
  x_ = x;
}
void Thing::setY(int y){
  y_ = y;
}
void Thing::setVx(int vx){
  velocityX_ = vx;
}

void Thing::setVy(int vy){
  velocityY_ = vy;
}

void Thing::move(int windowMaxX, int windowMaxY){
  x_ += velocityX_;
  y_ += velocityY_;
  
  if ( x_ < 0 || y_ < 0 || (x_+width_) > windowMaxX || (y_+height_) > windowMaxY )
  {
    offScreen = true;
  }
  else
  {
    // update QRectF displayed
    QPointF p( x_, y_ );
    QRectF r( rect() );
    r.moveTo(p);
    setRect( r );
  }
}

void Thing::setPic(QGraphicsPixmapItem* pic){
  pic_ = pic;
}

bool Thing::dead(){
  if (health_ == 0)
    return true;
  else
    return false;
}

bool Thing::collide(Thing* t){
  int rangeX = width_ - x_;
  int rangeY = height_ - y_;
  
  if (t->getX() < rangeX && t->getX() > x_ && t->getY() < rangeY && t->getY() > y_)
    return true;
  else
    return false;
}
