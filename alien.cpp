#include "alien.h"
/** Constructor. Alien appears at a random position above the screen and moves down into it in a random way. Has maxHealth of 3.
  @param pic the QPixmap to represent the alien
  @param w the width of the rocket
  @param h the height of the rocket
  @param rf the number by which the alien's velocity will be modulo'd by to produce random velocities
  @param onScreenFor the number of times the alien can move randomly before moving in a straight line off screen and dieing.*/
Alien::Alien(QPixmap* pic, int w, int h, int rf) : Thing(pic, rand()%(rf+1), 0-h, w, h, rand()%(rf+1), rand()%(rf+1), 3)
{
  randFactor_ = rf+1;
  lifeTime_ = 50; // decrements every time it moves
  offScreen = false;
  dead = false;
  collisionCounts = true;
}

/** Default constructor */
Alien::Alien(){}
/** Destructor */
Alien::~Alien(){}

/** Function that takes in the size of the available area to move and moves the alien by its velocity. Then sets velocity to a random number for the next time move is called. lifetime_ is decremented each time the alien moves this way. When lifetime_ = 0, the velocity stays constant and no longer sets randomly. When the alien's position is off-screen, its offScreen flag is set to true. 
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
      offScreen = true;
        
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

/** Function that returns true when the Alien intersects with a Thing. If it does, it decrements the Thing's health by 10 while decrementing its own by 1
  @param rocket the Thing that the Alien is checking if its intersecting
*/
bool Alien::collidesWith(Thing* rocket){
  bool collide = collidesWithItem(rocket, Qt::IntersectsItemShape);
  if (rocket->getPic() == pic_)
    return false;
  if (collide && collisionCounts)
  {
    rocket->decrementHealth(5);
    decrementHealth(1);
    //collisionCounts = false;
    if (rocket->dead) // if rocket's health is 0, flags offScreen
      rocket->offScreen = true;
    return true;
  }
  else
    return false;
}
