#include "clickscene.h"

ClickScene::ClickScene(MainWindow* m) : QGraphicsScene()
{
  mainwindow = m;
}

ClickScene::~ClickScene(){}

void ClickScene::mousePressEvent(QGraphicsSceneMouseEvent *e){
  mousePoint = e->scenePos();
  cout << "coord: " << mousePoint.x() << " "<< mousePoint.y() << endl;
  mainwindow->shootLaser(mousePoint.x(), mousePoint.y());
}
