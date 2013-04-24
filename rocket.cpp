#include "rocket.h"
#include <QBrush>

#define speed 5
using namespace std;

Rocket::Rocket(int windowMaxX, int windowMaxY, double w, double h, int vx, int vy, int maxHealth ) : Thing(windowMaxX, windowMaxY, w, h, vx, vy, maxHealth) {

  lives = 4; // start with 4 lives
  
  // SHOULD BE starting the rocket in the center bottom of screen. But isn't.
  x_ = (windowMaxX-w)/2;
  y_ = windowMaxY-h;
  width_ = w;
  height_ = h;
  health_ = maxHealth;
  velocityX_ = vx;
  velocityY_ = vy;
  
  QGraphicsPixmapItem* pic = new QGraphicsPixmapItem(QPixmap("images/rocket.jpg"));
  setPic(pic);
  //since pic isn't working right now
  setBrush(Qt::red);
}

Rocket::Rocket(){
}


Rocket::~Rocket(){
}

void Rocket::keyPressEvent(QKeyEvent* e)
{
  switch(e->key())
  {
    case Qt::Key_Up:
      setVx(0);
      setVy(-speed);
      move();
      break;
    case Qt::Key_Left:
      setVx(-speed);
      setVy(0);
      move();
      break;
    case Qt::Key_Right:
      setVx(speed);
      setVy(0);
      move();
      break;
    case Qt::Key_Down:
      setVx(0);
      setVy(speed);
      move();
      break;
    default:
      break;
  }
}

void Rocket::displayHealth(QLabel* label){
  QString string = "Health: ";
  string.append(  QString::number(health_) );
  string.append("Lives: ");
  string.append(  QString::number(lives) );
  
  // if health goes to zero, decrement number of lives and replenish health bar
  if (Thing::dead() && lives > 0) 
  {
    lives--;
    health_ = maxHealth_;
  }
  // if on last life and dead, game over
  else if (Thing::dead() && lives == 0)
  {
    string.clear();  
    string = "Game over";
  }
  
  label->setText(string);
  label->setHidden(false); 
}

