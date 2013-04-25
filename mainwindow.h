#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include <QtGui>
#include <QFormLayout>
#include <QString>

#include "thing.h"
#include "planet.h"
#include "rocket.h"
#include "missile.h"
#include "alien.h"
#include "star.h"
#include "meteor.h"
#include "laser.h"
#include "mylist.h"

#define WINDOW_MAX_X 250*2
#define WINDOW_MAX_Y 300*2

#define speed 5

class MainWindow : public QWidget{
  Q_OBJECT;
  
  public:
    explicit MainWindow();
    ~MainWindow();
    
    void show();
  
  private:
    QFormLayout* layout;
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
    
    QTimer* gameTimer;
    QPushButton* gameTimerButton;
    QTimer* addNewObjectsTimer;
    QPushButton* stopButton;
    QPushButton* playButton;
    QLabel* message;
    QLabel* score;
    int points;
  
  public slots:
    void handlegameTimer();
    void triggergameTimer();
    void startGame();
    
    void handleaddNewObjectsTimer();
    void triggeraddNewObjectsTimer();
};

#endif // MAINWINDOW_H
