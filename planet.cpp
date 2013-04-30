#include "planet.h"

using namespace std;

Planet::Planet(QPixmap* pic, int x, int y, int w, int h) : Thing(pic, x, y, w, h, 0, 0, 100) {
  // velocity is always 0 -- this item doesn't move
  //maxhealth is 100 - basically can't be killed
  collisionCounts = true;
}


Planet::Planet(){
}

Planet::~Planet(){
}


/** A function that determines whether or not the planet has collided with another Thing object. Returns true if a Planet is collided with a Thing, false otherwise. When true, kills the rocket by decrementing it's current health to 0. */
bool Planet::collidesWith(Thing* rocket){
  if (rocket->getPic() == pic_)
    return false;
  bool collide = collidesWithItem(rocket, Qt::IntersectsItemShape);
  if (collide && collisionCounts)
  {
    rocket->decrementHealth(50);
    collisionCounts = false;
    return true;
  }
  else
  {
//    collisionCounts = true;
    return false;
  }
}
