#include "thing.h"




using namespace std;




// Thing(startX, startY, width, height, velX, velY, maxHealth)
Thing::Thing(QPixmap* pic, double nx, double ny, double w, double h, int vx, int vy, int maxHealth ) : QGraphicsPixmapItem(*pic) {
  x_ = nx;
  y_ = ny;
  width_ = w;
  height_ = h;
  maxHealth_ = maxHealth;
  health_ = maxHealth_;
  velocityX_ = vx;
  velocityY_ = vy;
  pic_ = pic;
  
  offScreen = false;
  
  setPos(x_,y_);
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


int Thing::getWidth(){
  return width_;
}

int Thing::getHeight(){
  return height_;
}

int Thing::getHealth(){  
  return health_;
}

int Thing::getMaxHealth(){  
  return maxHealth_;
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

void Thing::decrementHealth(int num){
  if (health_ - num < 0)
    health_ = 0;
  else
    health_ -= num;
}

void Thing::move(){

  x_ += velocityX_;
  y_ += velocityY_;

/*
  cout <<"v's: " << velocityX_ << " "<<velocityY_ << endl;
  cout << x_ << " " << y_<<endl;
  cout << endl;
*/

  setPos(x_,y_);
}

void Thing::move(int windowMaxX, int windowMaxY){
  
  if (!offScreen)
  {
    x_ += velocityX_;
    y_ += velocityY_;
    
    if ( ((x_+width_) < 0 || (y_+height_) < 0 )|| (x_ > windowMaxX || y_ > windowMaxY))
      offScreen = true;
   
    setPos(x_,y_);
  }
}

bool Thing::dead(){
  if (health_ == 0)
    return true;
  else
    return false;
}

void Thing::die(){
  delete this;
}

bool Thing::collide(Thing* t){
  int rangeX = width_ - x_;
  int rangeY = height_ - y_;
  
  if (t->getX() < rangeX && t->getX() > x_ && t->getY() < rangeY && t->getY() > y_)
  {
    return true;
    cout<<"coliide"<<endl;
  }
  else
    return false;
}

void Thing::setPos(int x, int y){
  x_ = x;
  y_ = y;
  
  QGraphicsPixmapItem::setPos(x,y);
}
