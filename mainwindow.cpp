#include "mainwindow.h"

using namespace std;

MainWindow::MainWindow(){
  scene = new QGraphicsScene;
  view = new QGraphicsView(scene);
}

void MainWindow::show(){
  view->show();
}


MainWindow::~MainWindow(){
  delete scene;
  delete view;
}

