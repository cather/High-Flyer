#include "rocket.h"
#include <QBrush>

using namespace std;

/** Constructor. Sets the position to the center bottom of the screen.
  @param pic the QPixmap to represent the rocket
  @param windowMaxX the max x size of the window
  @param windowMaxY the max y size of the window
  @param w the width of the rocket
  @param h the height of the rocket
  @param speed the speed the rocket will move
  @param maxHealth the maxHealth of the rocket
*/
Rocket::Rocket(QPixmap* pic, int GAME_WINDOW_MAX_X, int GAME_WINDOW_MAX_Y, int w, int h, int speed, int maxHealth) : 
  Thing(pic, (GAME_WINDOW_MAX_X-pic->width())/2, (GAME_WINDOW_MAX_Y-pic->height()), w, h, speed, speed, maxHealth) {
  speed_ = speed;
  stars_ = 0;
  direction = -1;
  lives = 4; // start with 4 lives
  gameOver = false;
  setPos(x_,y_);
}
/** Constructor */
Rocket::Rocket(){
}

/** Destructor */
Rocket::~Rocket(){
}

/** Returns number of lives the rocket has*/
int Rocket::getLives(){ return lives;}

/** overloaded keypress event that sets the direction of the rocket to move in the move() function*/
void Rocket::keyPressEvent(QKeyEvent* e)
{
  if (!gameOver)
  { 
    switch(e->key())
    { 
      case Qt::Key_Up:
        direction = 0;
        break;
      case Qt::Key_Left:
        direction = 1;
        break;
      case Qt::Key_Right:
        direction = 2;
        break;
      case Qt::Key_Down:
        direction = 3;
        break;
      default:
        direction = -1;
        break;
    }
  }
}

/** Updates the rocket's health and number of lives in a QLabel
  @param label the QLabel to update with health and life information
*/
void Rocket::displayHealth(QLabel* label){
  QString string = "" ;
  
  // if health goes to zero, decrement number of lives and replenish health bar
  if (Thing::dead && lives > 0) 
  {
    lives--;
    health_ = maxHealth_;
    string.append("Health: " + QString::number(health_));
    string.append(" Lives: " + QString::number(lives) );
  }
  // if on last life and dead, print game over
  else if (Thing::dead && lives == 0)
  {
    gameOver = true;
    string.clear();  
    string = "Game over";
  }
  
  label->setText(string);
}

/** returns how many stars collected */
int Rocket::getStars(){
  return (stars_);
}

/** Function that returns true if colliding with another Thing, false otherwise*/
bool Rocket::collidesWith(Thing* t){
  bool collide = collidesWithItem(t, Qt::IntersectsItemShape);
  if (t->getPic() == pic_)
    return false;
  return collide;
}

/** Moves the rocket in the direction given by the keypressevent function. If the rocket is moved off screen, moves the rocket back on screen
  @param windowMaxX the x-area the rocket can move in without being considered offScreen
  @param windowMaxY the y-area the rocket can move in without being considered offScreen
*/
void Rocket::move(int windowMaxX, int windowMaxY)
{
  if (!gameOver){
    // based on direction, which was determined by keypressevents, sets velocities
    switch(direction)
    {
      case 0: // move up
        setVx(0);
        setVy(-speed_);
        break;
      case 1: //move left    
        setVx(-speed_);
        setVy(0);
        break;
      case 2: //move right
        setVx(speed_);
        setVy(0);
        break;
      case 3: //move down
        setVx(0);
        setVy(speed_);
      default:
        break;
    }
    
    // updates x,y positions
    x_ += velocityX_;
    y_ += velocityY_;
    
    // if offScreen as a result of the position change, reverts the change
    if ( x_ < 0 || y_ < 0 || (x_+width_) > windowMaxX || (y_+height_) > windowMaxY)
    {
      x_ -= velocityX_;
      y_ -= velocityY_;
    }
    
    //changes visible position on screen
    setPos(x_,y_);

    // re-initializes info for next key press event to reset
    direction = -1;
    setVx(0);
    setVy(0);
  }
}

