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


  // updates health every clock
  rocket->displayHealth(message);
  points++;
  QString string = "Score: " + QString::number(points);
  score->setText(string);

}


MainWindow::MainWindow(){
  layout = new QGridLayout();
  scene = new QGraphicsScene();
  view = new QGraphicsView(scene);
  string bg = "star.png";
  scene->setSceneRect(0,0,WINDOW_MAX_X*3/4, WINDOW_MAX_Y*3/4);

  //view->setLayout(layout);
  view->setFixedSize( WINDOW_MAX_X, WINDOW_MAX_Y);
  view->setWindowTitle("High Flyer");
   
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
  layout->setRowMinimumHeight(1, 100);
  layout->addWidget(view, 2, 1, 1, -1); // need to put game view at r2c1
  
  timerButton->show();
  
  //add this stuff below menu bar
  layout->addWidget(message, 3, 1);
  layout->addWidget(score,3 , 2);
  
  
   
  // creates rocket
  points = 0;
  double width, height, xv, yv;
  width = 80.0; height = 100.0; xv = 5; yv = 5;
  rocket = new Rocket( WINDOW_MAX_X*3/4, WINDOW_MAX_Y*3/4, 10, 20, xv, yv, maxRocketLife );
  scene->addItem(rocket);
  rocket->grabKeyboard();
  thingList.push_back(rocket);
  
  //planet
  planet = new Planet(100,0,20,30);
  scene->addItem(planet);
  thingList.push_back(planet);
  
  /*
  //missile test
//  int x, int y, int speed, int lifeSpan, Rocket* rocketToChase
  missile = new Missile (100, 100, 15, 30, rocket);
  scene->addItem(missile);
  thingList.push_back(missile);
  */
  
  /*
  //meteor test
  double y = rand()%WINDOW_MAX_Y, w = 100, h = 100, velocity = 15, hEalth = 10;
  meteor = new Meteor (y, w, h, velocity, hEalth);
  scene->addItem(meteor);
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
  view->show();
}

MainWindow::~MainWindow(){
  delete scene;
  delete view;
  for (int i = 0, n = thingList.size(); i<n; i++)
    delete thingList[i];
}

