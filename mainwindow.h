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
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QImage>
#include <QGraphicsTextItem>

#include "clickscene.h"
#include "thing.h"
#include "rocket.h"
#include "laser.h"
#include "alien.h"
#include "missile.h"
#include "meteor.h"
#include "planet.h"
#include "star.h"
#include "megastar.h"
#include "mylist.h"

#define BIG_WINDOW_MAX_X 500
#define BIG_WINDOW_MAX_Y 600
#define GAME_WINDOW_MAX_X BIG_WINDOW_MAX_X*9/10
#define GAME_WINDOW_MAX_Y BIG_WINDOW_MAX_Y*9/10

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
    ClickScene* gameScene;
    QGraphicsView* gameView;
    QGraphicsScene* bigScene;
    QGraphicsView* bigView;
    
    QGridLayout* highscoretablelayout;
    QGraphicsScene* scoreScene;
    QGraphicsView* scoreView;
    
    Rocket* rocket;
    Laser* laser;
    Alien* alien;
    Missile* missile;
    Meteor* meteor;
    Planet* planet;
    Star* star;
    Megastar* megastar;
    
    QPixmap* rocketPic;
    QPixmap* planetPic;
    QPixmap* starPic;
    QPixmap* missilePic;
    QPixmap* alienPic;
    QPixmap* laserPic;
    QPixmap* meteorPic;
    QPixmap* meteorBigPic;
    QPixmap* megastarPic;
    QImage* bg1;
    QImage* bg2;
    QImage* bg3;
    
    MyList<Thing*> thingList;
    
    QTimer* gameTimer;
    QPushButton* resetButton;
    QPushButton* stopButton;
    QPushButton* playButton;
    QPushButton* nameButton;
    QLabel* message;
    QLabel* health;
    QLabel* score;
    QLabel* name;
    QLabel* nameMenuLabel;
    QLabel* highscoretabletitle;
    QTextEdit* nameField;
    
    /** file containing high scores */
    QFile* scoreFile;
    /** bool to determine when to make high scores visible on screen*/
    bool scoresVisible;
    /** List of QLabels for each rank number in my scoring display*/
    MyList<QLabel*> scoreRank;
    /** List of QLabels for each player's name in my scoring display*/
    MyList<QLabel*> scoreName;
    /** List of QLabels for each player's score in my scoring display*/
    MyList<QLabel*> scoreTotal;
    
    QString playerName;
    
    /** Number to modulo a random number by to determine meteor movement speed*/
    int meteorSpeedrf;
    /** Speed at which meteors move at a minimum*/
    int minMeteorSpeed;
    
    /** Keeps track of what level of the game the player is on*/
    int level;
    /** Keeps track of whether or not a laser can be created based on game conditions */
    bool validToShoot;
    /** keeps track of whether user has entered a name in the nameField*/
    bool enteredName;
    /** Keeps track of user's earned points*/
    int points;
    /** keeps track of how many times the gametimer times out*/
    int counter;
    /** keeps track of how long until the timer times out*/
    int clockTime;
    /** keeps track of where the mouse is clicking in order to create a laser going in the correct direction*/
    QPoint mousePoint;
    /** keeps track of how many stars the user earned*/
    int starPoints;
    
  
  public slots:
    void handleTimer();
    void triggerTimer();
    void resetGame();
    void startGame();
    void endGame();
    void toggleHighScores();
    void updateHighScores();
    
  signals:
    void clicked();
};

#endif // MAINWINDOW_H
