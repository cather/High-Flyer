#include "rocket.h"
#include <QBrush>

using namespace std;

Rocket::Rocket(QPixmap* pic, int windowMaxX, int windowMaxY, double w, double h, int speed, int maxHealth) : Thing(pic, (windowMaxX-w)/2, windowMaxY-h, w, h, 0, 0, maxHealth) {

  cout << windowMaxX << " " << windowMaxY << endl;
  cout << x_ << " " << y_ << endl;
  cout << (windowMaxX-w)/2 << " " << windowMaxY-h << endl;
  lives = 4; // start with 4 lives
  gameOver = false;
  pause = true;
  speed_ = speed;
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
        move();
        break;
      case Qt::Key_Left:
        setVx(-speed_);
        setVy(0);
        move();
        break;
      case Qt::Key_Right:
        setVx(speed_);
        setVy(0);
        move();
        break;
      case Qt::Key_Down:
        setVx(0);
        setVy(speed_);
        move();
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

void Rocket::offScreen(){
  x_ -= velocityX_;
  y_ -= velocityY_;
  cout <<"Off screen"<<endl;

  setPos(x_,y_);
}
