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
#define GAME_WINDOW_MAX_X BIG_WINDOW_MAX_X*9/10
#define GAME_WINDOW_MAX_Y BIG_WINDOW_MAX_Y*9/10

class ClickScene;

class MainWindow : public QWidget{
  Q_OBJECT;
  
  public:
    explicit MainWindow();
    ~MainWindow();
    void show();
    void shootLaser(int x, int y);
    
  private:
    QGridLayout* layout;
    
    ClickScene* gameScene;
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
