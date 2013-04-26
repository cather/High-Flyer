#ifndef THING_H
#define THING_H

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QBrush>
#include <iostream>

#define rocketHealth = 10
#define alienHealth = 3;
#define missileHealth = 1;
#define starHealth = 1;
#define planetHealth = 1;
#define laserHealth = 1;

#define rocketWidth 50
#define rocketHeight 100
#define rocketSpeed 5
#define rocketMaxLife 100

#define alienWidth 50
#define alienHeight 100

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
    int getWidth();
    int getHeight();
    
    
    void setX(int x);
    void setY(int y);
    void setVx(int vx);
    void setVy(int vy);
    void move(int windowMaxX, int windowMaxY);
    void move();
    void setPos(int x, int y);
    
    int getHealth();
    void decrementHealth(int num);
    void die();
    
    int getMaxHealth();
    
    bool offScreen;
  
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
    
  public slots:
  
  signals:

};
#endif // THING_H
