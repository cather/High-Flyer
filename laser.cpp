#include "laser.h"
using namespace std;

/* Constructor that makes the laser's starting position the top-middle of the Rocket's. Maxhealth is 1.
  @param pix the QPixmap to represent the Laser
  @param vx the x-velocity of the laser
  @param xy the y-velocity of the laser
  @pram rocket the Rocket from which the laser gets information about its starting position  */
Laser::Laser(QPixmap* pic, int w, int h, int vx, int vy, Rocket* rocket) :
  Thing(pic, rocket->getX()+(rocket->getWidth()/2), rocket->getY()-20, w, h, vx, vy, 1 ){
  offScreen = false;
  dead = false;
}

/** Constructor */
Laser::Laser(){

}
/** Destructor */
Laser::~Laser(){
}

/** Sets velocity equal to a number corresponding to the mouse's position on the screen
  @param mousePointX the x coord of the mouseclick
  @param mousePointY the y coord of the mouseclick
*/
void Laser::shoot(int mousePointX, int mousePointY){
  int xvel = (mousePointX - x_)/velocityX_;
  int yvel = (mousePointY-y_) / velocityY_;
  setVx( xvel );
  setVy( yvel );
}

/** If colliding with a Thing, decrements that Thing's health by 1, kills itself and returns true. Returns false otherwise.
  @param enemy the Thing the Laser checks if it's intersecting
*/
bool Laser::collidesWith(Thing* enemy){
  bool collide = collidesWithItem(enemy, Qt::IntersectsItemShape);
  if (collide == true)
  {
    enemy->decrementHealth(1); // hurts enemy
    die(); // kills self
  }
  return collide;
}
