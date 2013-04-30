#include "missile.h"
using namespace std;

/** Constructor
  maxhealth is 1
*/
Missile::Missile(QPixmap* pic, int x, int y, int w, int h, int speed, int lifeSpan, Rocket* rocketToChase, QPixmap* explosion ) : 
  Thing(pic, x, y, w, h, (rocketToChase->getX() - x_)/10,  (rocketToChase->getY() - y_)/10 , 1) {
 
 
 /* in constructor before:
 ( rocket->getX() - x_ )/abs(( rocket->getX() - x_ )), 
  ( rocket->getY() - y_ )/ abs(( rocket->getY() - y_ ))
*/
  rocket_ = rocketToChase;
  speed_ = speed;
  explosionCounter = 10;

  
  time = lifeSpan;
  width_ = pic_->width();
  height_ = pic_->height();
  offScreen = false;
  dead = false;
  collisionCounts = true;
}

Missile::Missile(){
}

Missile::~Missile(){
}

// this should be checked at every clock
void Missile::move(int windowMaxX, int windowMaxY){
  velocityX_ = ( rocket_->getX() - x_ )/ 10 * speed_;
  velocityY_ = ( rocket_->getY() - y_ )/ 10 * speed_;
  x_ += velocityX_;
  y_ += velocityY_;
  
  setPos(x_,y_);
  explosionCounter--;
  if (explosionCounter == 0)
      explode();
  
  if ( (x_+width_)< 0  ||  (y_+height_)< 0 || (x_ > windowMaxX ) || ( y_ > windowMaxY ) )
    offScreen = true;
   

/*
  if (firstMove)
    velocityX_ = 2*velocityX_;
    
  if (!offScreen && !dead)
  {
    if (down)
    {
      x_ -= velocityX_;
      down = false;
    }
    else
    {
      x_ += velocityX_;
      down = true;
    }
    y_ += velocityY_;
    
    health_--;
      
    if ( ( (x_+width_) < 0 || ( y_+height_) < 0 )|| ( x_ > windowMaxX || y_ > windowMaxY ) )
      offScreen = true;
   
    setPos(x_,y_);
    time--;
  }
  
  if (firstMove)
  {
    velocityX_ = velocityX_/2;
    firstMove = false;
  }
  
  if (dead)
  {
    y_ += 2*velocityY_;
    if ( 
      ( (x_+width_) < 0 || ( y_+height_) < 0 )|| 
      ( x_ > windowMaxX || y_ > windowMaxY ) )
      offScreen = true;
   
    setPos(x_,y_);
  }
  
  */
}

void Missile::explode(){
  // leave a pixmap of explosion for 5 seconds, missile dies
  //scene_->addItem(explosion_);

  health_ = 0;
  offScreen = true;
  
}

bool Missile::collidesWith(Thing* enemy){
  bool collide = collidesWithItem(enemy, Qt::IntersectsItemShape);
  if (enemy->getPic() == pic_)
    return false;
  if (collide && collisionCounts)
  {
    enemy->decrementHealth(10);
    explode();
    collisionCounts = false;
    return true;
  }
  else
    return false;
}
