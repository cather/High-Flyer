#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include <QtGui>
#include <QGridLayout>
#include <QBoxLayout>
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

#define maxRocketLife 100
#define meteorDamage maxRocketLife/5
#define missileHitDamage maxRocketLife
#define missileRadiusDamage maxRocketLife/5
#define alienDamage maxRocketLife/2
#define planetDamage maxRocketLife

class MainWindow : public QWidget{
  Q_OBJECT;
  
  public:
    explicit MainWindow();
    ~MainWindow();
    
    void show();
  
  private:
    QGridLayout* layout;
    
    QGraphicsScene* gameScene;
    QGraphicsView* gameView;
    QGraphicsScene* bigScene;
    QGraphicsView* bigView;
    Rocket* rocket;
    Laser* laser;
    Meteor* meteor;
    Alien* alien;
    Missile* missile;
    Planet* planet;
    Star* star;
    
    MyList<Thing*> thingList;
    
    QTimer* gameTimer;
    QPushButton* timerButton;
    QPushButton* stopButton;
    QPushButton* playButton;
    QLabel* message;
    QLabel* score;
    int points;
  
  public slots:
    void handleTimer();
    void triggerTimer();
    void startGame();
};

#endif // MAINWINDOW_H
