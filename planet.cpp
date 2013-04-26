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

// if the planet is touching the rocket, kill the rocket and destroy the planet
bool Planet::collide(Thing* rocket){
  cout<<"D"<<endl;
  if (Thing::collide(rocket) == "rocket")
  {
    cout << "Touching"<<endl;
    rocket->decrementHealth(rocket->getHealth()); // kills rocket
    return true;
  }
  return false;
}
