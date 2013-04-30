#include "thing.h"
using namespace std;

/** Constructor
  param pic the QPixmap to represent the thing
  param nx the Thing's left-most x coord
  param ny the Thing's bottom-most y coord
  param vx the value of the x-velocity
  param xy the value of the y-velocity
  param maxHealth the value of the Thing's maximum possible health level
*/
Thing::Thing(QPixmap* pic, double nx, double ny, int w, int h, int vx, int vy, int maxHealth ) : QGraphicsPixmapItem(*pic) {
  x_ = nx;
  y_ = ny;
  velocityX_ = vx;
  velocityY_ = vy;
  maxHealth_ = maxHealth;
  health_ = maxHealth_;
  pic_ = pic;

  width_ = w;
  height_ = h;
  offScreen = false;
  dead = false;
  
  setPos(x_,y_);

}

Thing::Thing(){}
Thing::~Thing(){}
int Thing::getX(){ return x_; }
int Thing::getY(){ return y_; }
int Thing::getWidth(){ return width_; }
int Thing::getHeight(){ return height_; }
QPixmap* Thing::getPic(){ return pic_; }
int Thing::getHealth(){ return health_; }
int Thing::getMaxHealth(){ return maxHealth_; }
void Thing::setX(int x){ x_ = x; }
void Thing::setY(int y){ y_ = y; }
void Thing::setVx(int vx){ velocityX_ = vx; }
void Thing::setVy(int vy){ velocityY_ = vy; }

void Thing::decrementHealth(int num){
  //cout << "Decrementing  health"<<endl;
  health_ = health_ - num;
  if (health_ - num < 0)
    health_ = 0;
    
  if (health_ == 0)
    dead = true;
}

void Thing::move(int windowMaxX, int windowMaxY){  

  if (!dead)
  {
    x_ += velocityX_;
    y_ += velocityY_;
    if ( x_ < 0 || y_ < 0 || (x_+width_) > windowMaxX || (y_+height_) > windowMaxY)
    {
      offScreen = true;
    }
    setPos(x_,y_);
  }
}

bool Thing::collidesWith(Thing* r){
  if (r->getPic() == pic_)
    return false;
  return collidesWithItem(r, Qt::IntersectsItemShape);
}

void
 Thing::setPos(int x, int y){
  x_ = x;
  y_ = y;
  
  QGraphicsPixmapItem::setPos(x,y);
}
