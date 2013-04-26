#include "meteor.h"

Meteor::Meteor(QPixmap* pic, int y, int vx, int maxHealth ): Thing(pic, 0, y, vx, 0, maxHealth) {
  hit = false;
}

Meteor::Meteor(){
}

Meteor::~Meteor(){
}

void Meteor::die(){
  delete this;
}
