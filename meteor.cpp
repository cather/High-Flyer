#include "meteor.h"
using namespace std;
Meteor::Meteor(QPixmap* pic, int y, int vx ): Thing(pic, -50, y, vx, 0, 1) {
  hit = false;
}

Meteor::Meteor(){
}

Meteor::~Meteor(){
}

bool Meteor::collidesWith(Thing* enemy){
  if (collidesWithItem(enemy, Qt::IntersectsItemShape))
  {
    enemy->decrementHealth(20); // hurts enemy by 20 points
  }
  return collidesWithItem(enemy, Qt::IntersectsItemShape);
}
