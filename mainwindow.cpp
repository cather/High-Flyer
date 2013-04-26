#include "mainwindow.h"

using namespace std;

void MainWindow::startGame() {
  rocket->displayHealth(message);
  rocket->decrementHealth(10); // testing health
}

void MainWindow::triggerTimer() {
    if ( gameTimer->isActive() )
    {
      gameTimer->stop();
      playButton->setText("Play");  
    }
    else
    {
      gameTimer->start();
      playButton->setText("Pause");
    }
}
void MainWindow::handleTimer() {

  planet->collide(rocket); // checking if planet collides with rocket

  rocket->displayHealth(message); // update health
  points++; // update score
  score->setText("Score: " + QString::number(points)); // update score

}


MainWindow::MainWindow(){
  layout = new QGridLayout();
  
  bigScene = new QGraphicsScene();
  bigView = new QGraphicsView(bigScene);
  gameScene = new QGraphicsScene();
  gameView = new QGraphicsView(gameScene);
  bigView->setLayout(layout);
  
  //gameView->setLayout(layout);
  gameScene->setSceneRect(0,0,WINDOW_MAX_X*3/4, WINDOW_MAX_Y*3/4);
  gameView->setFixedSize( WINDOW_MAX_X, WINDOW_MAX_Y);
  gameView->setWindowTitle("High Flyer");
   
  // buttons
  playButton = new QPushButton("Play");
  stopButton = new QPushButton("Quit");
  timerButton = new QPushButton("Decrement health test");
  
  // Timer to keep track of score, health, etc
  gameTimer = new QTimer(this);
  gameTimer->setInterval(500); // half a second

  // qlabel for displaying health and lives
  message = new QLabel();
  score = new QLabel();

  layout->addWidget(playButton, 1, 1);
  layout->addWidget(stopButton, 1, 2);
  layout->addWidget(timerButton, 1, 3);
  layout->setRowMinimumHeight(1, 50);
  layout->addWidget(gameView, 2, 1, 1, -1); // need to put gameview at r2c1
  
  timerButton->show();
  
  //add this stuff below menu bar
  layout->addWidget(message, 3, 1, 1, 3);
  layout->addWidget(score,3 , 3);
  
  
   
  // creates rocket
  points = 0;
  double width, height, xv, yv;
  width = 80.0; height = 100.0; xv = 5; yv = 5;
  rocket = new Rocket( WINDOW_MAX_X*3/4, WINDOW_MAX_Y*3/4, 10, 20, xv, yv, maxRocketLife );
  gameScene->addItem(rocket);
  rocket->grabKeyboard();
  thingList.push_back(rocket);
  
  //planet
  planet = new Planet(100,0,20,30);
  gameScene->addItem(planet);
  thingList.push_back(planet);
  
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

  
  

  
  
  
  // connections (eventually combine startGame and triggerTime, get rid of timerButton)
  connect(gameTimer, SIGNAL(timeout()), this, SLOT(handleTimer()));
  connect(playButton, SIGNAL(clicked()), this, SLOT(triggerTimer()));
  connect(timerButton, SIGNAL(clicked()), this, SLOT(startGame())); // decrement health
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

