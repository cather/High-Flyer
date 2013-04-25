#ifndef ROCKET_H
#define ROCKET_H

#include "thing.h"
#include <QLabel>

/* Rocket movement will be controlled by arrow keys. Starting position is center bottom of screen */

class Rocket : public Thing {
  public:
  
    Rocket(int windowMaxX, int windowMaxY, double w, double h, int vx, int vy, int maxHealth );
    Rocket();
    ~Rocket();
    void dead();
    void displayHealth(QLabel* label);
    
  protected:
    void keyPressEvent(QKeyEvent* e);

  private:
    int lives;
    bool gameOver;
    
    
};
#endif //ROCKET_H
