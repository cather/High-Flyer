#include "laser.h"
using namespace std;

/* Constructor that makes the laser's starting position the top-middle of the Rocket's. Maxhealth is 1.
  @param pic the QPixmap to represent the Laser
  @param w the width of the laser
  @param h the height of the laser
  @param vx the x-velocity of the laser
  @param xy the y-velocity of the laser
  @pram rocket the Rocket from which the laser gets information about its starting position  */
Laser::Laser(QPixmap* pic, int w, int h, int vx, int vy, Rocket* rocket) :
  Thing(pic, rocket->getX()+(rocket->getWidth()/2), rocket->getY()-20, w, h, vx, vy, 1 ){
  offScreen = false;
  dead = false;
}

/** Constructor */
Laser::Laser(){}
/** Destructor */
Laser::~Laser(){}

/** Sets velocity equal to a number corresponding to the mouse's position on the screen
  @param mousePointX the x coord of the mouseclick
  @param mousePointY the y coord of the mouseclick
*/
void Laser::shoot(int mousePointX, int mousePointY){
  int xvel = (mousePointX - x_)/10;
  int yvel = (mousePointY-y_) / 10;
  setVx( xvel );
  setVy( yvel );
}

/** If colliding with a Thing, decrements that Thing's health by 1 and returns true. Returns false otherwise.
  @param enemy the Thing the Laser checks if it's intersecting
*/
bool Laser::collidesWith(Thing* enemy){
  if (enemy->getPic() == pic_)
    return false;

  bool collide = collidesWithItem(enemy, Qt::IntersectsItemShape);
  if (collide && collisionCounts)
  {
    enemy->decrementHealth(1); // hurts enemy
    collisionCounts = false; // can't collide anymore
    return true;
  }
  else
    return false;
}
