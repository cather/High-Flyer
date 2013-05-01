#include "clickscene.h"

ClickScene::ClickScene(MainWindow* m) : QGraphicsScene()
{
  mainwindow = m;
}

ClickScene::~ClickScene(){}

void ClickScene::mousePressEvent(QGraphicsSceneMouseEvent *e){
  mousePoint = e->scenePos();
  mainwindow->shootLaser(mousePoint.x(), mousePoint.y()); // calls the MainWindow's shootLaser function
}

