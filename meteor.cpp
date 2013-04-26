#include "meteor.h"

Meteor::Meteor(QPixmap* pic, int y, int vx ): Thing(pic, -50, y, vx, 0, 1) {
  hit = false;
  damageFactor = 2;
}

Meteor::Meteor(){
}

Meteor::~Meteor(){
}

void Meteor::collide(Thing* rocket){
  if (Thing::collide(rocket) && rocket->identifier == "rocket"){
    rocket->decrementHealth(damageFactor);
  }
}
