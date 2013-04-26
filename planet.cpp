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
bool Planet::collide(Rocket* rocket){
cout<<"D"<<endl;
  Thing::collide(rocket);
  if (1)
  {
    cout << "Touching"<<endl;
    rocket->decrementHealth(rocket->getHealth());
    decrementHealth(1);
    return true;
  }
  return false;
}
