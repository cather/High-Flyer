#include "mainwindow.h"

using namespace std;

void MainWindow::startGame() {
  rocket->displayHealth(message);
}

void MainWindow::triggerTimer() {
    if ( timer->isActive() )
    {
      timer->stop();
      timerButton->setText("Turn timer on");    
      rocket->decrementHealth(10); // testing health
    }
    else
    {
      timer->start();
      timerButton->setText("Turn timer off");
    }
}
void MainWindow::handleTimer() {
 // rocket->move( WINDOW_MAX_X, WINDOW_MAX_Y );
 
  // updates health every clock
  rocket->displayHealth(message);
  
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

