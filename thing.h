#ifndef THING_H
#define THING_H

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QBrush>
#include <iostream>

/** A generic class Things from which the rest of my game's objects can inherit from. Things have an x,y position, width, height, pixmapitem, and velocities in x,y .Things can move, detect when touching another Thing, detect when run out of health and detect when off-screen. 

@author Cathy Ji*/

class Thing : public QObject, public QGraphicsPixmapItem{
  public:

    Thing(QPixmap* pix, double nx, double ny, int w, int h, int vx, int vy, int maxHealth );
    Thing();
    ~Thing();

    int getX();
    int getY();
    int getWidth();
    int getHeight();
    QPixmap* getPic();
    
    void setX(int x);
    void setY(int y);
    void setVx(int vx);
    void setVy(int vy);
    void setPos(int x, int y);
    
    virtual void move(int windowMaxX, int windowMaxY);
    virtual bool collidesWith(Thing* r);
    
    int getHealth();
    void decrementHealth(int num);
    void die();
    
    int getMaxHealth();
    std::string identifier; // get rid of this. 
    
    /** Flag that is true when the Item is not within the parameters of the area in which it is allowed to move*/
    bool offScreen;
    /** Flag that is true when both health is 0 and offScreen is true*/
    bool dead;
  
  protected:
    /** The X coord of the Thing's left-most point*/
    int x_;
    /** The Y coord of the Thing's bottom-most point*/    
    int y_;
    /** The rate at which the Thing will move in the x-direction*/
    int velocityX_;
    /** The rate at whcih the Thing will move in the y-direction*/
    int velocityY_;
    /** The width of the Thing*/
    int width_;
    /** The height of the Thing*/
    int height_;
    /** The current health level*/
    int health_;
    /** The Thing's maximum possible amount of health*/
    int maxHealth_;
    /** The Thing's picture visualization*/
    QPixmap* pic_;

};
#endif // THING_H
