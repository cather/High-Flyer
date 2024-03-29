#include "missile.h"
using namespace std;

/** Constructor. Missiles have maxhealth of 1 and velocities directed towards a Rocket item
  @param pic the QPixmap to represent the Missile
  @param w the width of the Missile
  @param h the height of the Missile
  @param speed the speed of the Missile
  @param lifeSpan how many times the Missile can move before it explodes
  @param rocketToChase the Rocket that the Missile changes its velocity to move towards
*/
Missile::Missile(QPixmap* pic, int x, int y, int w, int h, int speed, Rocket* rocketToChase) : 
  Thing(pic, x, y, w, h, (rocketToChase->getX() - x_)/50*speed,  (rocketToChase->getY() - y_)/50*speed , 1) {
  rocket_ = rocketToChase;
  speed_ = speed;
  explosionCounter = 100;
  recalculateCounter = 5;
  
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
  if (recalculateCounter == 0 )
  {
    velocityX_ = ( rocket_->getX() - x_ )/20  * speed_;
    velocityY_ = ( rocket_->getY() - y_ )/20 * speed_;
    recalculateCounter = 5;
  }
  recalculateCounter--;
  
  x_ += velocityX_;
  y_ += velocityY_;
  setPos(x_,y_);
  
  // keep track of counter
  explosionCounter--;
  if (explosionCounter == 0)
      explode();

  // keep track of whether on screen or not
  if ( (x_+width_)< 0  ||  (y_+height_)< 0 || (x_ > windowMaxX ) || ( y_ > windowMaxY ) )
    offScreen = true;
}

/** function that makes the missile die*/
void Missile::explode(){
  health_ = 0;
  offScreen = true;
  
}

/** function that detects whether Missile intersects another Thing for the first time. Returns true if yes, false otherwise. If true, decrements the Thing's health and explodes
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
