#ifndef ROCKET_H
#define ROCKET_H

#include "thing.h"
#include <QLabel>

/* Rocket movement will be controlled by arrow keys. Starting position is center bottom of screen */

class Rocket : public Thing {
  public:
  
    Rocket(QPixmap* pic, int windowMaxX, int windowMaxY, int speed, int maxHealth);
    Rocket();
    ~Rocket();
    void dead();
    void displayHealth(QLabel* label);
    int getStars();
    void offScreen(); // override offScreen
    bool pause;
    void addStar();
    bool collide(Rocket* r);
    
  protected:
    void keyPressEvent(QKeyEvent* e);

  private:
    int lives;
    bool gameOver;
    int speed_;
    int starsCollected_;
};
#endif //ROCKET_H
