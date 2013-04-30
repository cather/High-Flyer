#include "star.h"
using namespace std;
/** Constructor. All stars had velocities of 0 and maxHealth of 1
    @param pix the QPixmap the represent the star
    @param x the x coord to appear
    @param y the y coord to appear
    @param w the width of the Star
    @param h the height of the Star
*/
Star::Star(QPixmap* pic, int x, int y, int w, int h) : Thing(pic, x, y, w, h, 5, 20, 1) {
  offScreen = false;
  collisionCounts = true;
  firstMove = true;
  down = true;
}

/** Default constructor */
Star::Star(){
}
/** Destructor */
Star::~Star(){
}
/** Returns true if the star is intersecting with a Thing, false otherwise. If true, adds 1 to the Thing's star_ count and flags offScreen as true
  @param rocket the Thing the star is checking if it's colliding with
*/
bool Star::collidesWith(Thing* rocket){
  if (rocket->getPic() == pic_)
      return false;

    bool collide = collidesWithItem(rocket, Qt::IntersectsItemShape);
    if (collide && collisionCounts)
    {
      rocket->addStar(); // hurts adds star
      offScreen = true;
      collisionCounts = false;
      return true;
    }
    else
      return false;
}

void Star::move(int windowMaxX, int windowMaxY)
{
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
  }
  
  if (firstMove)
  {
    velocityX_ = velocityX_/2;
    firstMove = false;
  }
  
  if (dead)
  {
    y_ += 2*velocityY_;
    if ( ( (x_+width_) < 0 || ( y_+height_) < 0 )|| (x_ > windowMaxX || y_ > windowMaxY ) )
      offScreen = true;
   
    setPos(x_,y_);
  }
}
