#include "meteor.h"
using namespace std;
Meteor::Meteor(QPixmap* pic, int y, int vx ): Thing(pic, -50, y, vx, 0, 1) {
  hit = false;
  damageFactor = 20;
}

Meteor::Meteor(){
}

Meteor::~Meteor(){
}

void Meteor::collide(Thing* rocket){
  if (Thing::collide(rocket) == "rocket"){
    cout << "Dcrement"<<endl;
    rocket->decrementHealth(damageFactor);
  }
}
