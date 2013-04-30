#include "meteor.h"
using namespace std;
/** Constructor. All meteors start at coord -50, 0 and have y-velocity of 0, maxHealth of 1
  @param pic the QPixmap to represent the meteor
  @param y the y position of the meteor
  @param vx the x-velocity of the meteor */
Meteor::Meteor(QPixmap* pic, int y, int w, int h, int vx) : Thing(pic, -50, y, w, h, vx, 0, 1){
  offScreen = false;
  collisionCounts = true;
  dead = false;
}

/** constructor*/
Meteor::Meteor(){
}
/** destructor */
Meteor::~Meteor(){
}
/** If colliding with a Thing, decrements that Thing's health and kills itself and returns true. Returns false otherwise.
  @param enemy the Thing the Meteor checks if it's intersecting
*/
bool Meteor::collidesWith(Thing* enemy){
  bool collide = collidesWithItem(enemy, Qt::IntersectsItemShape);
  if (enemy->getPic() == pic_)
    return false;
  if (collide && collisionCounts)
  {
    decrementHealth(1);
    enemy->decrementHealth(10);
    collisionCounts = false;
    return true;
  }
  else
    return false;
}

void Meteor::move(int windowMaxX, int windowMaxY){  
  x_ += velocityX_;
  y_ += velocityY_;
  if (y_ < 0 || x_ > windowMaxX || (y_+height_) > windowMaxY)
    offScreen = true;
    
  setPos(x_,y_);
}
