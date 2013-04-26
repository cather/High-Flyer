#include "planet.h"


Planet::Planet(int x, int y, double w, double h) : Thing(x, y, w, h, 0, 0, 1) {
  //just need to set position and dimensions
  
  QGraphicsPixmapItem* pic = new QGraphicsPixmapItem(QPixmap("images/rocket.jpg"));
  setPic(pic);
  //since pic isn't working right now
  setBrush(Qt::black);
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
