#include "alien.h"
/** Constructor. The alien has a maxHealth of 3 and starts with intial coordinates 0,0
  @param pic the QPixmap to represent the alien
  @param rf the number by which the alien's velocity will be modulo'd by to produce random velocities
  @param onScreenFor the number of times the alien can move randomly before moving in a straight line off screen and dieing.*/
Alien::Alien(QPixmap* pic, int w, int h, int rf) : Thing(pic, 0, 0, w, h, rand()%(rf+1), rand()%(rf+1), 3)
{

  // maxHealth is 3
  // velocities are random 
  randFactor_ = rf+1;
  lifeTime_ = 50; // decrements every time it moves
  width_ = pic_->width();
  height_ = pic_->height();
  offScreen = false;
  dead=false;

}
/** Default constructor */
Alien::Alien(){
}
/** Destructor */
Alien::~Alien(){
}
/** Function that takes in the size of the available area to move and moves the alien by its velocity. If the alien's position is off-screen, its offScreen flag is set to true
    @param windowMaxX the width of the space the Alien can move in and be considered on screen
    @param windowMaxY the height of the space the Alien can move in and be considered on screen
    */
void Alien::move(int windowMaxX, int windowMaxY){
   // updates x, y positions based on velocities
    x_ += velocityX_;
    y_ += velocityY_;
    setPos(x_,y_);

    // check whether offScreen
    if ( (x_+width_)< 0  ||  (y_+height_)< 0 || (x_ > windowMaxX ) || ( y_ > windowMaxY ) )
    {
      offScreen = true;
    }
        
    if (lifeTime_ != 0 && !dead && !offScreen )
    {
      int mag = rand()%3;
      switch(mag)
      {
        case 0:
          setVx(rand()%randFactor_);
          setVy(rand()%randFactor_);
          break;
        case 1:      
          setVy(- rand()%randFactor_);
          setVy(rand()%randFactor_);
          break;
        case 2:
          setVx(- rand()%randFactor_);
          setVy(- rand()%randFactor_);
          break;
        case 3:
          setVx(rand()%randFactor_);
          setVy(- rand()%randFactor_);
          break;
      }
      lifeTime_--; // decrement amount of time left to move
    }
  
}

/** Function that returns true when the Alien intersects with a Thing. If it does, it cuts the health of the Thing in half
  @param rocket the Thing that the Alien is checking if its intersecting
*/
bool Alien::collidesWith(Thing* rocket){
  bool collide = collidesWithItem(rocket, Qt::IntersectsItemShape);
  if (rocket->getPic() == pic_)
    return false;
  if (collide)
  {
    decrementHealth(1);
    rocket->decrementHealth(1);
    if (rocket->dead)
    {
      rocket->offScreen = true;
      rocket->hide();
    }
  }
  return collide;
}
