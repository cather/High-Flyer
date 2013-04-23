#ifndef THING_H
#define THING_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsRectItem>

/*Things can move, detect when touching another Thing, detect when run out of health and detect when off-screen. Things have an x,y position, width, height, pixmapitem, and velocities in x,y*/

class Thing : public QObject, public QGraphicsRectItem{
  public:
    Thing(double nx, double ny, double w, double h, int vx, int vy, int maxHealth );
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
    void move(int x, int y);
    void setPic(QGraphicsPixmapItem* pic);
  
  protected:
    int x_;
    int y_;
    int velocityX_;
    int velocityY_;
    int width_;
    int height_;
    int health_;
    QGraphicsPixmapItem* pic_;
    
    bool offScreen;
  
  public slots:
  
  signals:

};
#endif // THING_H
