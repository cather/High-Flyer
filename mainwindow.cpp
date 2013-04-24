#include "mainwindow.h"

using namespace std;

void MainWindow::startGame() {
  message = new QLabel("Starting");
  layout->addRow(message);
}

void MainWindow::triggerTimer() {
    if ( timer->isActive() )
    {
      timer->stop();
      timerButton->setText("Turn timer on");
    }
    else
    {
      timer->start();
      timerButton->setText("Turn timer off");
    }
}
void MainWindow::handleTimer() {
 // rocket->move( WINDOW_MAX_X, WINDOW_MAX_Y );
}

MainWindow::MainWindow(){
  layout = new QFormLayout();
  scene = new QGraphicsScene();
  view = new QGraphicsView(scene);
  view->setLayout(layout);
  view->setFixedSize( WINDOW_MAX_X, WINDOW_MAX_Y);
  view->setWindowTitle("High Flyer");

  double x, y, width, height, xv, yv, health;
  x = rand()%WINDOW_MAX_X;
  y = rand()%WINDOW_MAX_Y;
  width = 80.0;
  height = 100.0;
  xv = 5;
  yv = 5;
  health = 100;
  

  rocket = new Rocket( x, y, width, height, xv, yv, health );
  
  scene->addItem(rocket);
  
  thingList.push_back(rocket);
  
  timer = new QTimer(this);
  timerButton = new QPushButton("Trigger Timer");
  timerButton->setGeometry(0,0,100,25);

  // Insert button into layout
  layout->addRow(timerButton);
  timerButton->show();
  
  timer->setInterval(5); // 5 milliseconds
  connect(timer, SIGNAL(timeout()), this, SLOT(handleTimer()));
  connect(timerButton, SIGNAL(clicked()), this, SLOT(triggerTimer()));
  
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

