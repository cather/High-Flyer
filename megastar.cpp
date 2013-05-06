#include "megastar.h"

using namespace std;
/** Constructor. All Megastars (initially) move diagonally down the screen and have maxHealth of 1
    @param pix the QPixmap the represent the Megastar
    @param x the x coord at which to appear
    @param y the y coord at which to appear
    @param w the width of the Megastar
    @param h the height of the Megastar
    @param speed the speed the Megastar will move
    @param rocketToAvoid the Rocket that the Megastar moves away from
*/
Megastar::Megastar(QPixmap* pic, int x, int y, int w, int h, int speed, Rocket* rocketToAvoid) : Thing(pic, x, y, w, h, speed, speed, 1) {
  offScreen = false;
  collisionCounts = true;
  rocket_ = rocketToAvoid;
  speed_ = speed;
}

/** Default constructor */
Megastar::Megastar(){}
/** Destructor */
Megastar::~Megastar(){}

/** Returns true if the Megastar is intersecting with a Thing, false otherwise. If true, adds 1 to the Thing's megastar_ count and flags offScreen as true
  @param rocket the Thing the Megastar is checking if it's colliding with
*/
bool Megastar::collidesWith(Thing* rocket){
  if (rocket->getPic() == pic_)
      return false;

  bool collide = collidesWithItem(rocket, Qt::IntersectsItemShape);
  if (collide && collisionCounts)
  {
    rocket->addMegastar(); // adds Megastar
    offScreen = true;
    collisionCounts = false;
    return true;
  }
  else
    return false;
}

/** The function that makes the Megastar move to avoid the rocket
  @param windowMaxX the x-area the Megastar can move in without being considered offScreen
  @param windowMaxY the y-area the Megastar can move in without being considered offScreen
*/void Megastar::move(int windowMaxX, int windowMaxY)
{

  int diffX = rocket_->getX() - (x_+width_);
  int diffY = rocket_->getY() - (y_+height_);
  
  //if within a certain range of the rocket, moves to avoid it
  if (diffX < 15 && diffY < 15)
  {
    velocityX_ = (x_ - rocket_->getX())/15*speed_;
    velocityY_ = (y_ - rocket_->getY())/15*speed_;
  }
  // otherwise, moves diagonally at original speed
  else
  {
    velocityX_ = speed_;
    velocityY_ = speed_;
  }
  
  x_ += velocityX_;
  y_ += velocityY_;
  setPos(x_,y_);
 
  // keep track of whether on screen or not
  if ( (x_+width_)< 0  ||  (y_+height_)< 0 || (x_ > windowMaxX ) || ( y_ > windowMaxY ) )
    offScreen = true;
    
}
