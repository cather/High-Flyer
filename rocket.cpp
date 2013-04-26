#include "rocket.h"
#include <QBrush>

using namespace std;

Rocket::Rocket(QPixmap* pic, int windowMaxX, int windowMaxY, int speed, int maxHealth) : Thing(pic, (windowMaxX-pic->width())/2, windowMaxY-pic->height(), 0, 0, maxHealth) {
  lives = 4; // start with 4 lives
  gameOver = false;
  pause = true;
  speed_ = speed;
  starsCollected_ = 0;
  identifier = "rocket";
}

Rocket::Rocket(){
}


Rocket::~Rocket(){
}
 
// need some way to pass in (int windowMaxX, int windowMaxY) to stop rocket from moving off screen
void Rocket::keyPressEvent(QKeyEvent* e)
{
  if (!gameOver && pause == false)
  {
    switch(e->key())
    { 
      case Qt::Key_Up:
        setVx(0);
        setVy(-speed_);
        move(x_+width_*2, y_+height_);
        break;
      case Qt::Key_Left:
        setVx(-speed_);
        setVy(0);
        move(x_+width_*2, y_+height_);
        break;
      case Qt::Key_Right:
        setVx(speed_);
        setVy(0);
        move(x_+width_*2, y_+height_);
        break;
      case Qt::Key_Down:
        setVx(0);
        setVy(speed_);
        move(x_+width_*2, y_+height_);
        break;
      default:
        break;
    }
  }
}

void Rocket::displayHealth(QLabel* label){
  QString string = "Health: " + QString::number(health_);
  string.append(" Lives: " + QString::number(lives) );
  
  // if health goes to zero, decrement number of lives and replenish health bar
  if (Thing::dead() && lives > 0) 
  {
    lives--;
    health_ = maxHealth_;
  }
  // if on last life and dead, game over
  else if (Thing::dead() && lives == 0)
  {
    gameOver = true;
    string.clear();  
    string = "Game over";
  }
  
  label->setText(string);
}

int Rocket::getStars(){
  return (starsCollected_*50);
}

void Rocket::offScreen(){
  x_ -= velocityX_;
  y_ -= velocityY_;
  cout <<"Off screen"<<endl;

  setPos(x_,y_);
}
bool Rocket::collide(Thing* t){
  if (Thing::collide(t) != "")
  {
    if(Thing::collide(t) == "star")
      starsCollected_ += 1;
    
    return true;
  }
  return false;
}


