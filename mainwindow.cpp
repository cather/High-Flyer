#include "mainwindow.h"

using namespace std;

#define rocketWidth 50
#define rocketHeight 100
#define rocketSpeed 5
#define rocketMaxLife 100

void MainWindow::mouseMoveEvent(QMouseEvent *e){
  cout << "mouse"<<endl;
  mousePoint = e->pos();
  emit shootLaser(mousePoint.x(), mousePoint.y());
}

void MainWindow::triggerTimer() {

  if (enteredName)
  {
    if ( gameTimer->isActive() )
    {
      gameTimer->stop();
      playButton->setText("Play");
      rocket->pause = true;
    }
    else
    {
      gameTimer->start();
      playButton->setText("Pause");
      rocket->pause = false;
    }
  }
}

void MainWindow::startGame() {
  enteredName = true;
  QString n = enterName->toPlainText();
  
  name->setText(n);
  nameButton->hide();
  enterName->hide();

  starting = false;
  rocket->show();
  rocket->setPos((GAME_WINDOW_MAX_X-(rocket->getWidth()))/2, GAME_WINDOW_MAX_Y);
  rocket->pause = false;
  rocket->grabKeyboard();

  gameTimer->start();
  playButton->setText("Pause");
}


void MainWindow::resetGame(){
  enteredName = false;
  nameButton->show();
  enterName->show();
  starting = true;
  gameTimer->stop();
  playButton->setText("Play");
  points = 0;
  counter = 0;
  rocket->hide();

  // keep rocket, delete everything else

  for (int i = 1; i < thingList.size(); i++)
    thingList[i]->hide();
     
  message->setText("Health: ---  Lives: -");
  score->setText("Score: -");
}

void MainWindow::handleTimer() {
  if (counter > 0 && counter % 15 == 0)
  {  
    //planet
    planet = new Planet(planetPic, 100, 0, 20, 30);
    gameScene->addItem(planet);
    thingList.push_back(planet);
   }
  
  // clockTime starts at 500 ms => level up after 10 seconds -> clockTime = 5000
  if (counter > 0 && counter % 30 == 0)
  {
    cout << "Level up"<<endl;
    clockTime += clockTime;
    gameTimer->setInterval(clockTime);
  }

  if (planet != NULL)
    planet->collide(rocket); // checking if planet collides with rocket

  rocket->displayHealth(message); // update health
  points++; // update score
  score->setText("Score: " + QString::number(points)); // update score
  counter++; // update timer counter
}


MainWindow::MainWindow(){

  enteredName = false;
  starting = true;
  clockTime = 200;
  counter = 0;
  
  // storing graphics  
  rocketPic = new QPixmap("images/rocket.jpg");
  planetPic = new QPixmap("images/planets.jpg");
  starPic = new QPixmap("images/stars.jpg");
  missilePic = new QPixmap("images/missile.jpg");
  alienPic = new QPixmap("images/alien.jpg");
  laserPic = new QPixmap("images/laser.jpg");

  // construct layout
  layout = new QGridLayout();
  bigScene = new QGraphicsScene();
  bigView = new QGraphicsView(bigScene);
  gameScene = new QGraphicsScene();
  gameView = new QGraphicsView(gameScene);
  bigView->setLayout(layout);
  gameScene->setSceneRect(0, 0, GAME_WINDOW_MAX_X, GAME_WINDOW_MAX_Y);
  cout << GAME_WINDOW_MAX_X << " " << GAME_WINDOW_MAX_Y << endl;
  gameView->setFixedSize(BIG_WINDOW_MAX_X, BIG_WINDOW_MAX_Y);
  
  setMouseTracking(true);
  
  bigView->setWindowTitle("High Flyer");

  // buttons
  playButton = new QPushButton("Play");
  stopButton = new QPushButton("Quit");
  resetButton = new QPushButton("Restart");
  nameButton = new QPushButton("Enter");
  
  // Timer to keep track of score, health, etc
  gameTimer = new QTimer(this);
  gameTimer->setInterval(clockTime);

  // qlabel for displaying health and lives
  message = new QLabel();
  score = new QLabel();
  name = new QLabel();
  
  //qtextedit for name
  enterName = new QTextEdit();
    enterName->setFixedSize(100, 25);
    enterName->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  // add to scene
  gameScene->addWidget(enterName);
  gameScene->addWidget(nameButton);
  nameButton->setGeometry(0, enterName->height(), 100 ,25);
    
  // add everything to layout
  layout->addWidget(playButton, 1, 1);
  layout->addWidget(stopButton, 1, 2);
  layout->addWidget(resetButton, 1, 3);
  layout->setRowMinimumHeight(1, 50);
    layout->addWidget(gameView, 2, 1, 1, -1);
  layout->addWidget(name, 3, 1);
  layout->addWidget(message, 3, 2);
  layout->addWidget(score, 3, 3);
  
  // creates rocket
  points = 0;
  rocket = new Rocket(rocketPic, GAME_WINDOW_MAX_X, GAME_WINDOW_MAX_Y, rocketWidth, rocketHeight, rocketSpeed, rocketMaxLife);
  gameScene->addItem(rocket);
  rocket->setZValue(100);
  rocket->hide();
  thingList.push_back(rocket);
  message->setText("Health: ---  Lives: -");
  score->setText("Score: -"); // update score
  
  // connections
  connect(gameTimer, SIGNAL(timeout()), this, SLOT(handleTimer()));
  connect(nameButton, SIGNAL(clicked()), this, SLOT(startGame()));
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
  for (int i = 0; i < thingList.size(); i++)
    delete thingList[i];
}

