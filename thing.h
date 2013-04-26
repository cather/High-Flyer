#ifndef THING_H
#define THING_H

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QBrush>

#include <iostream>

/*Things can move, detect when touching another Thing, detect when run out of health and detect when off-screen. Things have an x,y position, width, height, pixmapitem, and velocities in x,y*/

class Thing : public QObject, public QGraphicsPixmapItem{
  public:
    Thing(QPixmap* pix, double nx, double ny, double w, double h, int vx, int vy, int maxHealth );
    Thing();
    ~Thing();
    bool collide(Thing* t);
    bool dead();
    
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    void setVx(int vx);
    void setVy(int vy);
    void move(int windowMaxX, int windowMaxY);
    void move();
    
    int getHealth();
    void decrementHealth(int num);
    void die();
    void offScreen();
    
    int getMaxHealth();
  
  protected:
    int x_;
    int y_;
    int velocityX_;
    int velocityY_;
    int width_;
    int height_;
    int health_;
    int maxHealth_;
    QPixmap* pic_;
    
  
    bool onScreen;
    
  
  public slots:
  
  signals:

};
#endif // THING_H
