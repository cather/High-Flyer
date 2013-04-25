#include "mainwindow.h"

using namespace std;

void MainWindow::startGame() {
  rocket->displayHealth(message);
  rocket->decrementHealth(10); // testing health
}

void MainWindow::triggergameTimer() {
    if ( gameTimer->isActive() )
    {
      gameTimer->stop();
      gameTimerButton->setText("Start gameTimer");  
    }
    else
    {
      gameTimer->start();
      gameTimerButton->setText("Stop gameTimer");
    }
}
void MainWindow::handlegameTimer() {
  // updates health every clock
  rocket->displayHealth(message);
  points++;
  QString string = "Score: " + QString::number(points);
  score->setText(string);
  
}

void MainWindow::triggeraddNewObjectsTimer() {
}

void MainWindow::handleaddNewObjectsTimer() {
  // add new Things to the screen every clock
  
  //testing meteor movement
  meteor->move(WINDOW_MAX_X, WINDOW_MAX_Y); 
//  addNewObjectsTimer->setInterval(rand()%20);
}


MainWindow::MainWindow(){
  layout = new QFormLayout();
  scene = new QGraphicsScene();
  view = new QGraphicsView(scene);
  view->setLayout(layout);
  view->setFixedSize( WINDOW_MAX_X, WINDOW_MAX_Y);
  view->setWindowTitle("High Flyer");
  
  // creates rocket
  points = 0;
  double width, height, xv, yv, health;
  width = 80.0; height = 100.0; xv = 5; yv = 5; health = 20;
  rocket = new Rocket( WINDOW_MAX_X, WINDOW_MAX_Y, width, height, xv, yv, health );
  scene->addItem(rocket);
  rocket->grabKeyboard();
  thingList.push_back(rocket);
  
  //create test meteor
  meteor = new Meteor (WINDOW_MAX_Y/2, 100, 100, 5, 0, 10);
  scene->addItem(meteor);
  thingList.push_back(meteor);
  
  // qlabel for displaying health and lives
  message = new QLabel();
  layout->addRow(message);
  score = new QLabel();
  layout->addRow(score);
  // message->setHidden(true);
  
  // Timer to keep track of score, health, etc
  gameTimer = new QTimer(this);
  gameTimerButton = new QPushButton("Trigger gameTimer");
  gameTimerButton->setGeometry(0,0,100,25);
  layout->addRow(gameTimerButton);
  gameTimerButton->show();
  // programming gameTimer
  gameTimer->setInterval(500); // half a second
  connect(gameTimer, SIGNAL(timeout()), this, SLOT(handlegameTimer()));
  connect(gameTimerButton, SIGNAL(clicked()), this, SLOT(triggergameTimer()));
  
  // timer to add new objects
  addNewObjectsTimer = new QTimer(this);  
  //programming addNewObjectsTimer
  addNewObjectsTimer->setInterval(10);
  //addNewObjectsTimer->setInterval(rand()%20);
  addNewObjectsTimer->start();
  connect(addNewObjectsTimer, SIGNAL(timeout()), this, SLOT(handleaddNewObjectsTimer()));
  
  playButton = new QPushButton("Hurt me test");
  layout->addRow(playButton);
  stopButton = new QPushButton("Quit");
  layout->addRow(stopButton);  
  // when clicked, starts game (??)
  connect(playButton, SIGNAL(clicked()), this, SLOT(startGame()));     
  //when clicked, exits out of app
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

