#include "planet.h"

using namespace std;

Planet::Planet(QPixmap* pic, int x, int y) : Thing(pic, x, y, 0, 0, 1) {
  // velocity is always 0 -- this item doesn't move
  //maxhealth is just 1
}


Planet::Planet(){
}

Planet::~Planet(){
}


/** A function that determines whether or not the planet has collided with another Thing object. Returns true if a Planet is collided with a Thing, false otherwise. When true, kills the rocket by decrementing it's current health to 0. */
bool Planet::collidesWith(Thing* rocket){
  cout<<"D"<<endl;
  if (collidesWithItem(rocket, Qt::IntersectsItemShape))
  {
    cout << "Touching somethins"<<endl;
    rocket->decrementHealth(rocket->getHealth()); // kills rocket
    return true;
  }
  return false;
}
