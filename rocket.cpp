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
  direction = -1;
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

void Rocket::keepOnScreen(){
  if (offScreen)
  {
    x_ -= velocityX_;
    y_ -= velocityY_;
    cout <<"Off screen"<<endl;

    setPos(x_,y_);
  }
}

bool Rocket::collidesWith(Thing* t){
  collidesWithItem(t, Qt::IntersectsItemShape);
}

void Rocket::move(int x, int y)
{
 switch(direction)
  {
    case 0: // up
      setVx(0);
      setVy(-speed_);
      break;
    case 1: //left    
      setVx(-speed_);
      setVy(0);
      break;
    case 2: // right
      setVx(speed_);
      setVy(0);
      break;
    case 3: //down
      setVx(0);
      setVy(speed_);
      break;
    default:
      setVx(0);
      setVy(0);
      break;
  }
  if (!gameOver && pause == false)
    Thing::move(x,y);
  keepOnScreen();
  //direction = -1;
}

