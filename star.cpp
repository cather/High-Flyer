#include "star.h"
using namespace std;
/** Constructor. All stars had velocities of 0 and maxHealth of 1
    @param pix the QPixmap the represent the star
    @param x the x coord to appear
    @param y the y coord to appear
*/
Star::Star(QPixmap* pic, int x, int y, int w, int h) : Thing(pic, x, y, w, h, 0, 0, 1) {
  offScreen = false;
  collisionCounts = true;
}

/** Default constructor */
Star::Star(){
}
/** Destructor */
Star::~Star(){
}
/** Returns true if the star is intersecting with a Thing, false otherwise
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

/** Signal to rocket to indicate it's collided with something*/
void Star::collected(){}
