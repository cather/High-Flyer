#ifndef ROCKET_H
#define ROCKET_H

#include "thing.h"
#include <QLabel>

/**  The player object of the game. Rocket movement will be controlled by arrow keys. Starting position is center of screen */

class Rocket : public Thing {
  public:
    Rocket(QPixmap* pic, int x, int y, int w, int h, int speed, int maxHealth);
    Rocket();
    ~Rocket();
    void dead();
    void displayHealth(QLabel* label);
    int getStars();
    int getMegastars();
    void keepOnScreen();
    void move(int windowMaxX, int windowMaxY);
    bool collidesWith(Thing* t);
    
  protected:
    void keyPressEvent(QKeyEvent* e);

  private:
    /** Flag for when rocket has no lives and 0 health */
    bool gameOver;
    /** Speed of the rocket */
    int speed_;
    /** Flag that the user sets through keyboard input. Controls direction of the rocket's movement*/
    int direction;
};
#endif //ROCKET_H
