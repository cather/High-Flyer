#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "thing.h"
#include "planet.h"
#include "rocket.h"
#include "missile.h"
#include "alien.h"
#include "star.h"
#include "meteor.h"
#include "laser.h"
#include "mylist.h"

#include <iostream>

using namespace std;

class MainWindow : pubic QWidget{
  Q_OBJECT;
  
  public:
    MainWindow();
    ~MainWindow();
  
  private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    Rocket* rocket;
    Laser* laser;
    Meteor* meteor;
    Alien* alien;
    Missile* missile;
    Planet* planet;
    Star* star;
    
    MyList<Thing*> thingList;
  
  public slots:
}

#endif
