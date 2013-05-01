#include "planet.h"

using namespace std;

/** Constructor. 
  @param pix the QPixmap to represent the planet
  @param x the planet's x coord
  @param y the planet's y cood
  @param w the planet's width
  @param h the planet's height
*/
Planet::Planet(QPixmap* pic, int x, int y, int w, int h) : Thing(pic, x, y, w, h, 0, 10, 100) {
  // x-velocity is always 0 -- this item only moves vertically
  //maxhealth is 100 - basically can't be killed
  collisionCounts = true;
}

/** Default constructor*/
Planet::Planet(){}
/** Destructor*/
Planet::~Planet(){}

/** A function that determines whether or not the planet has collided with another Thing object. Returns true if a Planet is collided with a Thing, false otherwise. When true, kills the rocket's life by decrementing it's health to 0. Can only collide with a Thing once.*/
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
