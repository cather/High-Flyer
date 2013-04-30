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
#include <QTextEdit>
#include <QMouseEvent>

#include "clickscene.h"

#include "thing.h"
#include "rocket.h"
#include "laser.h"
#include "alien.h"
#include "missile.h"
#include "meteor.h"
#include "planet.h"
/*

#include "star.h"
*/

#include "mylist.h"

#define BIG_WINDOW_MAX_X 500
#define BIG_WINDOW_MAX_Y 600
#define GAME_WINDOW_MAX_X BIG_WINDOW_MAX_X*9/10
#define GAME_WINDOW_MAX_Y BIG_WINDOW_MAX_Y*9/10


#define rocketHealth = 10
#define alienHealth = 3;
#define missileHealth = 1;
#define starHealth = 1;
#define planetHealth = 1;
#define laserHealth = 1;

#define rocketSpeed 20
#define rocketMaxLife 100

class ClickScene;

class MainWindow : public QWidget{
  Q_OBJECT;
  
  public:
    explicit MainWindow();
    ~MainWindow();
    void show();
    void shootLaser(int x, int y);
    void spawnMissile(int AlienMidx, int AlienMidy);
    
  private:
    QGridLayout* layout;
    QGraphicsItemAnimation* bg;
    
    ClickScene* gameScene;
    QGraphicsView* gameView;
    QGraphicsScene* bigScene;
    QGraphicsView* bigView;
    Rocket* rocket;
    Laser* laser;
    Alien* alien;
    Missile* missile;
    Meteor* meteor;
    Planet* planet;
    /*
    
    Star* star;
    */
    
    MyList<Thing*> thingList;
    
    QTimer* gameTimer;
    QPushButton* resetButton;
    QPushButton* stopButton;
    QPushButton* playButton;
    QPushButton* nameButton;
    QLabel* message;
    QLabel* score;
    QLabel* name;
    QLabel* nameMenuLabel;
    QTextEdit* enterName;
    
    bool validToShoot;
    bool enteredName;
    bool starting;
    int points;
    int counter;
    int clockTime;
    QPoint mousePoint;
    
    QPixmap* rocketPic;
    QPixmap* planetPic;
    QPixmap* starPic;
    QPixmap* missilePic;
    QPixmap* alienPic;
    QPixmap* laserPic;
    QPixmap* meteorPic;
    QPixmap* explosion;
  
  public slots:
    void handleTimer();
    void triggerTimer();
    void resetGame();
    void startGame();
    void endGame();
    
  signals:
    void clicked();
};

#endif // MAINWINDOW_H
