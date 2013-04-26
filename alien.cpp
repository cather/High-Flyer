#include "alien.h"

Alien::Alien(QPixmap* pic, int rf, int onScreenFor ) : Thing(pic, 0, 0, alienWidth, alienHeight, rand()%rf, rand()%rf, 3)
{
  // maxHealth is 3
  // velocities are random 
  randFactor_ = rf;
  lifeTime_ = onScreenFor; // decrement every_time it moves
  onScreen = true;
}

Alien::Alien(){
}

Alien::~Alien(){
}

void Alien::move(int windowMaxX, int windowMaxY){
  x_ += velocityX_;
  y_ += velocityY_;

  if (onScreen && lifeTime_ != 0)
  {
    if ( x_< 0 )
      onScreen = false;
    if ( y_< 0 )
      onScreen = false;
    if ( (x_+width_) > windowMaxX )
      onScreen = false;
    if ( (y_+height_) > windowMaxY )
      onScreen = false;

    setVx(rand()%randFactor_);
    setVy(rand()%randFactor_);
    lifeTime_--;
  }
  
  setPos(x_,y_);      
  
}
