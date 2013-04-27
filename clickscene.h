#ifndef CLICKSCENE_H
#define CLICKSCENE_H

#include "mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QPoint>
#include <iostream>
class MainWindow;

class ClickScene : public QGraphicsScene{
  public:
    ClickScene(MainWindow* m);
    ~ClickScene();
    void mousePressEvent(QGraphicsSceneMouseEvent *e);
    
  private:
    QPointF mousePoint;
    MainWindow* mainwindow;
    
  public slots:
    
  signals:
    void shootLaser(int, int);
};

#endif // CLICKYSCENE
