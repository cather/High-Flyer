#include "thing.h"
using namespace std;

/** Constructor for a Thing with a pic, position, width and height, velocities in the x and y direction, and a maximum health level
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
  collisionCounts = true;
  stars_ = 0;
  
  setPos(x_,y_);

}

/** Constructor*/
Thing::Thing(){}
/** Destructor*/
Thing::~Thing(){}
/** Returns x_ */
int Thing::getX(){ return x_; }
/** Returns y_ */
int Thing::getY(){ return y_; }
/** Returns width_*/
int Thing::getWidth(){ return width_; }
/** Returns height_*/
int Thing::getHeight(){ return height_; }
/** Returns pic*/
QPixmap* Thing::getPic(){ return pic_; }
/** Returns current health_ level*/
int Thing::getHealth(){ return health_; }
/** Returns max health*/
int Thing::getMaxHealth(){ return maxHealth_; }
/** Sets x_
@param x the new x coord
*/
void Thing::setX(int x){ x_ = x; }
/** Sets y_
@param y the new y coord
*/
void Thing::setY(int y){ y_ = y; }
/** Sets velocityX_
@param vx the new velocity in the x direction
*/
void Thing::setVx(int vx){ velocityX_ = vx; }
/** Sets velocityY_
@param vy the new velocity in the y direction
*/
void Thing::setVy(int vy){ velocityY_ = vy; }

/** Decreases current health_. If the result is less than 0, sets health_ to 0. If health = 0, flags the dead bool as true
@param num the number by which to decrease health_
*/
void Thing::decrementHealth(int num){
  health_ = health_ - num;
  if (health_ - num < 0)
    health_ = 0;
    
  if (health_ == 0)
    dead = true;
}

/** Moves the Thing. If it goes off screen, marks the offScreen flag as true
  @param windowMaxX the x-area the Thing can move in without being considered offScreen
  @param windowMaxY the y-area the Thing can move in without being considered offScreen
*/
void Thing::move(int windowMaxX, int windowMaxY){  

  if (!offScreen)
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

/** Pure virtual function*/
bool Thing::collidesWith(Thing* r){}

/** Sets position
@param x the new x position
@param y the new y position
*/
void Thing::setPos(int x, int y){
  x_ = x;
  y_ = y;
  
  QGraphicsPixmapItem::setPos(x,y);
}

/** Increases stars_ count by 1*/
void Thing::addStar(){
  stars_ += 1;
}
