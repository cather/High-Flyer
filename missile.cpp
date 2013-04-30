#include "missile.h"
using namespace std;

/** Constructor. Missiles have maxhealth of 1 and velocities directed towards a Rocket item
  @param pic the QPixmap to represent the Missile
  @param w the width of the Missile
  @param h the height of the Missile
  @param speed the speed of the Missile
  @param lifeSpan how many times the missile can move before it explodes
  @param rocketToChase the Rocket that the missile changes its velocity to move towards
  @param explosion the QPixmap to represent the missile's explosion
*/
Missile::Missile(QPixmap* pic, int x, int y, int w, int h, int speed, Rocket* rocketToChase, QPixmap* explosion ) : 
  Thing(pic, x, y, w, h, (rocketToChase->getX() - x_)/50,  (rocketToChase->getY() - y_)/50 , 1) {
  rocket_ = rocketToChase;
  speed_ = speed;
  explosionCounter = 10;
  
  offScreen = false;
  dead = false;
  collisionCounts = true;
}

/** Constructor */
Missile::Missile(){}
/** Destructor */
Missile::~Missile(){}

/** Moves the Missile in the direction of the rocket_. If moves off screen, marks offScreen true. Decrements explosionCounter_ at each call. When explosionCounter_ = 0, explode() is called
  @param windowMaxX the x-area the missile can move in without being considered offScreen
  @param windowMaxY the y-area the missile can move in without being considered offScreen
*/
void Missile::move(int windowMaxX, int windowMaxY){

  // set velocity to direction of rocket_
  velocityX_ = ( rocket_->getX() - x_ )/ x_ * speed_;
  velocityY_ = ( rocket_->getY() - y_ )/ y_ * speed_;
  
  if (rocket_->getX() - x_ > 50)
    velocityX_ = ( rocket_->getX() - x_ )/ 50 * speed_;
  else
   velocityX_ = ( rocket_->getX() - x_ ) * speed_;
  if ( rocket_->getY() - y_  > 50)
    velocityY_ = ( rocket_->getY() - y_ )/ 50 * speed_;
  else
    velocityY_ = ( rocket_->getY() - y_ ) * speed_;
  
  
  x_ += velocityX_;
  y_ += velocityY_;
  setPos(x_,y_);
  
  // keep track of counter
  //explosionCounter--;
  if (explosionCounter == 0)
      explode();

  // keep track of whether on screen or not
  if ( (x_+width_)< 0  ||  (y_+height_)< 0 || (x_ > windowMaxX ) || ( y_ > windowMaxY ) )
    offScreen = true;
}

/** function that makes the explosion_ Pixmap appear*/
void Missile::explode(){
  // leave a pixmap of explosion for 5 seconds, missile dies
  //scene_->addItem(explosion_);

  health_ = 0;
  offScreen = true;
  
}

/** function that detects whether Missile intersects another Thing for the first time. Returns true if yes, false otherwise. If true, decrements the THing's health and explodes
  @param enemy the Thing being checked for collision with the missile*/
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
