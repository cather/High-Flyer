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

#define BIG_WINDOW_MAX_X 500
#define BIG_WINDOW_MAX_Y 600

#define GAME_WINDOW_MAX_X BIG_WINDOW_MAX_X*3/4
#define GAME_WINDOW_MAX_Y BIG_WINDOW_MAX_Y*3/4

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
    QPushButton* resetButton;
    QPushButton* stopButton;
    QPushButton* playButton;
    QLabel* message;
    QLabel* score;
    int points;
    
    bool starting;
    int counter;
    int clockTime;
    
    QPixmap* rocketPic;
    QPixmap* planetPic;
    QPixmap* starPic;
    QPixmap* missilePic;
    QPixmap* alienPic;
    QPixmap* laserPic;
  
  public slots:
    void handleTimer();
    void triggerTimer();
    void resetGame();
};

#endif // MAINWINDOW_H
