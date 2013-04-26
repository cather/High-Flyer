#include "planet.h"

using namespace std;

Planet::Planet(QPixmap* pic, int x, int y, double w, double h) : Thing(pic, x, y, w, h, 0, 0, 1) {
  // velocity is always 0 -- this item doesn't move
}


Planet::Planet(){
}

Planet::~Planet(){
}

// if the planet is touching the rocket, kill the rocket and destroy the planet
void Planet::collide(Rocket* rocket){
 /*
  if (Thing::collide(rocket))
  {
    cout << "Touching"<<endl;
    rocket->decrementHealth(rocket->getHealth());
    decrementHealth(1);
  }
  */
}
