#include "mainwindow.h"

using namespace std;

#define rocketWidth 10
#define rocketHeight 20
#define rocketSpeed 5
#define rocketMaxLife 100

void MainWindow::triggerTimer() {
    if ( gameTimer->isActive() )
    {
      gameTimer->stop();
      rocket->pause = true;
      playButton->setText("Play");
    }
    else
    {
      gameTimer->start();
      playButton->setText("Pause");
      if (starting)
      {
        gameScene->addItem(rocket);
        rocket->grabKeyboard();
        starting = false;
      }
      rocket->pause = false;
    }
}

void MainWindow::resetGame(){
  starting = true;
  playButton->setText("Play");
  points = -1;
  counter = 0;
  
  // keep rocket, delete everything else
  for (int i = thingList.size()-1; i > 1; i++)
    delete thingList[i];
}

void MainWindow::handleTimer() {
  if (counter % 20 == 0)
  {  
    //planet
    planet = new Planet(100,0,20,30);
    gameScene->addItem(planet);
    thingList.push_back(planet);
 }
  
  /*
  //missile test
//  int x, int y, int speed, int lifeSpan, Rocket* rocketToChase
  missile = new Missile (100, 100, 15, 30, rocket);
  gameScene->addItem(missile);
  thingList.push_back(missile);
  */
  
  /*
  //meteor test
  double y = rand()%WINDOW_MAX_Y, w = 100, h = 100, velocity = 15, hEalth = 10;
  meteor = new Meteor (y, w, h, velocity, hEalth);
  gameScene->addItem(meteor);
  thingList.push_back(meteor);
  
  if (meteor->collide(laser))
  {
    meteor->die();
    laser->die();
  }
  else if (meteor->collide(rocket))
  {
    rocket->decrementHealth(meteorDamage);
    meteor->die();
  }
  */

  if (planet != NULL)
    planet->collide(rocket); // checking if planet collides with rocket

  rocket->displayHealth(message); // update health
  points++; // update score
  score->setText("Score: " + QString::number(points)); // update score
  counter++; // update timer counter
}


MainWindow::MainWindow(){
  counter = 0;
  starting = false;
  layout = new QGridLayout();
  bigScene = new QGraphicsScene();
  bigView = new QGraphicsView(bigScene);
  gameScene = new QGraphicsScene();
  gameView = new QGraphicsView(gameScene);
  bigView->setLayout(layout);
  
  gameScene->setSceneRect(0,0,GAME_WINDOW_MAX_X, GAME_WINDOW_MAX_Y);
  gameView->setFixedSize(BIG_WINDOW_MAX_X, BIG_WINDOW_MAX_Y);
  bigView->setWindowTitle("High Flyer");
   
  // buttons
  playButton = new QPushButton("Play");
  stopButton = new QPushButton("Quit");
  resetButton = new QPushButton("Restart");
  
  // Timer to keep track of score, health, etc
  gameTimer = new QTimer(this);
  gameTimer->setInterval(500); // half a second

  // qlabel for displaying health and lives
  message = new QLabel();
  score = new QLabel();

  // add everything to layout
  layout->addWidget(playButton, 1, 1);
  layout->addWidget(stopButton, 1, 2);
  layout->addWidget(resetButton, 1, 3);
  layout->setRowMinimumHeight(1, 50);
    layout->addWidget(gameView, 2, 1, 1, -1);
  layout->addWidget(message, 3, 1, 1, 3);
  layout->addWidget(score,3 , 3);
  
  // creates rocket
  points = -1;
  rocket = new Rocket(100,0, rocketWidth, rocketHeight, rocketSpeed, rocketMaxLife);
  thingList.push_back(rocket);


  // connections (eventually combine startGame and triggerTime, get rid of resetButton, add restart button)
  connect(gameTimer, SIGNAL(timeout()), this, SLOT(handleTimer()));
  connect(playButton, SIGNAL(clicked()), this, SLOT(triggerTimer()));
  connect(resetButton, SIGNAL(clicked()), this, SLOT(resetGame()));
  connect(stopButton, SIGNAL(clicked()), qApp, SLOT(quit()));
}

void MainWindow::show(){
  bigView->show();
}

MainWindow::~MainWindow(){
  delete gameScene;
  delete gameView;
  for (int i = 0, n = thingList.size(); i<n; i++)
    delete thingList[i];
}

