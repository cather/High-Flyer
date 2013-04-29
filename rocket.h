#ifndef ROCKET_H
#define ROCKET_H

#include "thing.h"
#include <QLabel>

/**  The player object of the game. Rocket movement will be controlled by arrow keys. Starting position is center bottom of screen */

class Rocket : public Thing {
  public:
  
    Rocket(QPixmap* pic, int x, int y, int w, int h, int speed, int maxHealth);
    Rocket();
    ~Rocket();
    void dead();
    void displayHealth(QLabel* label);
    int getStars();
    void keepOnScreen();
    bool pause;
    bool collidesWith(Thing* t); //same as in thing
    void move(int windowMaxX, int windowMaxY);
    int direction;
    int getLives();
    void loseLives(int i);
    
  protected:
    void keyPressEvent(QKeyEvent* e);

  private:
    /** number of lives the rocket has*/
    int lives;
    /** flag that's true if rocket has no lives and 0 health */
    bool gameOver;
    /** speed of the rocket */
    int speed_;
    /** number of stars the rocket has collided with */
    int starsCollected_;
};
#endif //ROCKET_H
