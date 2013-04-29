#include "missile.h"
using namespace std;
Missile::Missile(QPixmap* pic, int x, int y, int speed, int lifeSpan, Rocket* rocketToChase ) : Thing(pic, x, y, 30, 30, lifeSpan) {
 
 /* in constructor before:
 ( rocket->getX() - x_ )/abs(( rocket->getX() - x_ )), 
  ( rocket->getY() - y_ )/ abs(( rocket->getY() - y_ ))
*/
  rocket = rocketToChase;
  speed_ = speed;
  firstMove = true;
  down = true;
}

Missile::Missile(){
}

Missile::~Missile(){
}

// this should be checked at every clock
void Missile::move(int windowMaxX, int windowMaxY){
  //velocityX_ = ( rocket->getX() - x_ )/abs(( rocket->getX() - x_ )) * speed_;
  //velocityY_ = ( rocket->getY() - y_ )/ abs(( rocket->getY() - y_ )) * speed_;

  if (firstMove)
    velocityX_ = 2*velocityX_;
    
  if (!offScreen && !dead())
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
  }
  
  if (firstMove)
  {
    velocityX_ = velocityX_/2;
    firstMove = false;
  }
  
  if (dead())
  {
    y_ += 2*velocityY_;
    if ( 
      ( (x_+width_) < 0 || ( y_+height_) < 0 )|| 
      ( x_ > windowMaxX || y_ > windowMaxY ) )
      offScreen = true;
   
    setPos(x_,y_);
  }
}

bool Missile::collideWith(Thing* enemy){

  if (collidesWithItem(enemy, Qt::IntersectsItemShape))
  {
    enemy->decrementHealth(10);
  }
  
  return collidesWithItem(enemy, Qt::IntersectsItemShape);
}
