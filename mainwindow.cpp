#include "mainwindow.h"

using namespace std;

void MainWindow::startGame() {
  rocket->displayHealth(message);
}

void MainWindow::triggergameTimer() {
    if ( gameTimer->isActive() )
    {
      gameTimer->stop();
      gameTimerButton->setText("Start gameTimer");    
      rocket->decrementHealth(10); // testing health
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
  
}

void MainWindow::triggeraddNewObjectsTimer() {
}

void MainWindow::handleaddNewObjectsTimer() {
  // add new Things to the screen every clock  
}


MainWindow::MainWindow(){
  layout = new QFormLayout();
  scene = new QGraphicsScene();
  view = new QGraphicsView(scene);
  view->setLayout(layout);
  view->setFixedSize( WINDOW_MAX_X, WINDOW_MAX_Y);
  view->setWindowTitle("High Flyer");

  double width, height, xv, yv, health;

  width = 80.0; height = 100.0; xv = 5; yv = 5; health = 20;
  
  message = new QLabel();
  layout->addRow(message);
  message->setHidden(true);

  rocket = new Rocket( WINDOW_MAX_X, WINDOW_MAX_Y, width, height, xv, yv, health );
  scene->addItem(rocket);
  rocket->grabKeyboard();  

  thingList.push_back(rocket);
  
  gameTimer = new QTimer(this);
  gameTimerButton = new QPushButton("Trigger gameTimer");
  gameTimerButton->setGeometry(0,0,100,25);
  
  addNewObjectsTimer = new QTimer(this); // timer to add new objects

  // Insert button into layout
  layout->addRow(gameTimerButton);
  gameTimerButton->show();
  
  // programming gameTimer
  gameTimer->setInterval(5); // 1 milliseconds
  connect(gameTimer, SIGNAL(timeout()), this, SLOT(handlegameTimer()));
  connect(gameTimerButton, SIGNAL(clicked()), this, SLOT(triggergameTimer()));
  
  //programming addNewObjectsTimer
  addNewObjectsTimer->setInterval(rand()%20);
  connect(addNewObjectsTimer, SIGNAL(timeout()), this, SLOT(handleaddNewObjectsTimer()));
  
  
  playButton = new QPushButton("Play");
  layout->addRow(playButton);
  stopButton = new QPushButton("Quit");
  layout->addRow(stopButton);
  
  // when clicked, creates board
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
}

