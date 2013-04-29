#include "laser.h"
using namespace std;

/* Constructor that makes the laser's starting position the top-middle of the Rocket's. Maxhealth is 1.
  @param pix the QPixmap to represent the Laser
  @param vx the x-velocity of the laser
  @param xy the y-velocity of the laser
  @pram rocket the Rocket from which the laser gets information about its starting position  */
Laser::Laser(QPixmap* pic, int w, int h, int vx, int vy, Rocket* rocket) : Thing(pic, (rocket->getWidth()/2)+ rocket->getX(), rocket->getY()-10, w, h, vx, vy, 1 ){
  width_ = pic_->width();
  height_ = pic_->height();
  offScreen = false;
  cout << "laser " << x_<< " " << y_ <<endl;
}

/** Constructor */
Laser::Laser(){

}
/** Destructor */
Laser::~Laser(){
}

/** Moves laser*/
void Laser::shoot(int mousePointX, int mousePointY){
  int xvel = (mousePointX - x_) / velocityX_;
  int yvel = (mousePointY - y_) / velocityY_;
  
  setVx( xvel );
  setVy( yvel );
  cout << "laser v " << xvel << " "<<yvel<<endl;
}


/** If colliding with a Thing, decrements that Thing's health by 1, kills itself and returns true. Returns false otherwise.
  @param enemy the Thing the Laser checks if it's intersecting
*/
bool Laser::collidesWith(Thing* enemy){

  return collidesWithItem(enemy, Qt::IntersectsItemShape);
}
