#include "planet.h"


Planet::Planet(QPixmap* pic, int x, int y, double w, double h) : Thing(pic, x, y, w, h, 0, 0, 1) {
  //just need to set position and dimensions

}


Planet::Planet(){
}

Planet::~Planet(){
}

// if the planet is touching the rocket, kill the rocket and destroy the planet
void Planet::collide(Rocket* rocket){
  if (Thing::collide(rocket))
  {
    rocket->decrementHealth(rocket->getMaxHealth());
    decrementHealth(1);
  }  
}
