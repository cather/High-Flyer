#include "planet.h"

using namespace std;

/** Constructor. Planets have a picture, x,y position, width, and height. Velocity is always 0 in x direction and preset to 10 in y direction*/
Planet::Planet(QPixmap* pic, int x, int y, int w, int h) : Thing(pic, x, y, w, h, 0, 10, 100) {
  // x-velocity is always 0 -- this item only moves horizontally
  //maxhealth is 100 - basically can't be killed
  collisionCounts = true;
}

/** Default cosntructor*/
Planet::Planet(){}
/** Destructor*/
Planet::~Planet(){}

/** A function that determines whether or not the planet has collided with another Thing object. Returns true if a Planet is collided with a Thing, false otherwise. When true, kills the rocket by decrementing it's current health to 0. */
bool Planet::collidesWith(Thing* rocket){
  if (rocket->getPic() == pic_)
    return false;
  bool collide = collidesWithItem(rocket, Qt::IntersectsItemShape);
  if (collide && collisionCounts)
  {
    rocket->decrementHealth(rocket->getHealth());
    collisionCounts = false;
    return true;
  }
  else
  {
//    collisionCounts = true;
    return false;
  }
}
