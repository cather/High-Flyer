#include "alien.h"
/** Constructor. Alien appears at a random position above the screen and moves down into it in a random way, then exits with constant velocity if it hasn't left the screen already. Has maxHealth of 3.
  @param pic the QPixmap to represent the alien
  @param w the width of the alien
  @param h the height of the alien
  @param rf the number by which the alien's velocity will be modulo'd by to produce random velocities
  */
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

/** Function that takes in the size of the available area to move, and changes the alien's position by its velocity. Then sets velocity to a random number for the next time move is called. lifetime_ is decremented each time the alien moves this way. When lifetime_ = 0, the velocity stays constant and no longer sets randomly. When the alien's position is off-screen, its offScreen flag is set to true. 
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
        
    // checks whether appropriate to change velocity
    if (lifeTime_ != 0 && !dead && !offScreen )
    {
      int mag = rand()%3;
      switch(mag)
      {
        case 0: // move NE
          setVx(rand()%randFactor_);
          setVy(rand()%randFactor_);
          break;
        case 1: // move NW
          setVx(- rand()%randFactor_);
          setVy(rand()%randFactor_);
          break;
        case 2: // move SW
          setVx(- rand()%randFactor_);
          setVy(- rand()%randFactor_);
          break;
        case 3: // move SE
          setVx(rand()%randFactor_);
          setVy(- rand()%randFactor_);
          break;
      }
      lifeTime_--; // decrement amount of times allowed to move randomly
    }
  
}

/** Function that returns true when the Alien intersects with a Thing. If it does, it decrements the Thing's health by 10 while decrementing its own by 1
  @param rocket the Thing that the Alien is checking if its intersecting
*/
bool Alien::collidesWith(Thing* rocket){
  bool collide = collidesWithItem(rocket, Qt::IntersectsItemShape);

  // colliding with something that has the same pic (and therefore same classification as Alien) is the same as no collission
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
