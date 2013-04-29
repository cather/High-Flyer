#ifndef CLICKSCENE_H
#define CLICKSCENE_H

#include "mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QPoint>
#include <iostream>
class MainWindow;

/**
  A class that inherit from QGraphicsScene to overload the mousePressEvent and pass in information about the mouse's coordinates to a MainWindow
*/

class ClickScene : public QGraphicsScene{
  public:
    /** Constructor */
    ClickScene(MainWindow* m);
    /** Destructor */
    ~ClickScene();
    /** A function that takes in a mouseclick event and passes the mouse's x,y coordinates on the scene to a MainWindow */
    void mousePressEvent(QGraphicsSceneMouseEvent *e);
    
  private:
    /** The point at which the mouse has clicked*/
    QPointF mousePoint;
    /** The MainWindow to which the mouseclick information is being passed*/
    MainWindow* mainwindow;
};

#endif // CLICKYSCENE
