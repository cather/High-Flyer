#include "mainwindow.h"
using namespace std;


MainWindow::MainWindow(){
  validToShoot = false;
  enteredName = false;
  starting = true;
  clockTime = 50;
  counter = 0;
  int nW = 200, nH = 25; // variables for name elements
  
  // storing graphics  
  rocketPic = new QPixmap("images/rocket.png");
  planetPic = new QPixmap("images/planet.png");
  starPic = new QPixmap("images/star.png");
  missilePic = new QPixmap("images/missile.png");
  alienPic = new QPixmap("images/alien.png");
  laserPic = new QPixmap("images/laser.jpg");
  meteorPic = new QPixmap("images/meteor.png");
  explosion = new QPixmap("images/explosion.png");

  // construct layout
  layout = new QGridLayout();
  bigScene = new QGraphicsScene();
  bigView = new QGraphicsView(bigScene);
  gameScene = new ClickScene(this);
  gameView = new QGraphicsView(gameScene);
    gameScene->addPixmap(QPixmap("bg.png"));

    bigView->setLayout(layout);
    gameScene->setSceneRect(0, 0, GAME_WINDOW_MAX_X, GAME_WINDOW_MAX_Y);
    cout << "game scene: " << GAME_WINDOW_MAX_X << " " << GAME_WINDOW_MAX_Y << endl;
    gameView->setFixedSize(BIG_WINDOW_MAX_X, BIG_WINDOW_MAX_Y);
    
  // buttons
  playButton = new QPushButton("Play");
  stopButton = new QPushButton("Quit");
  resetButton = new QPushButton("Restart");
  nameButton = new QPushButton("Welcome Abord!");
    nameButton->setGeometry((GAME_WINDOW_MAX_X-nW)/2,(GAME_WINDOW_MAX_Y)/2+nH, nW, nH);
  
  // Timer to keep track of score, health, etc
  gameTimer = new QTimer(this);
  gameTimer->setInterval(clockTime);

  // qlabel for displaying health and lives
  message = new QLabel();
  score = new QLabel();
  name = new QLabel();
  nameMenuLabel = new QLabel("Enter your name:");
    nameMenuLabel->setFixedSize( nW, nH);
    nameMenuLabel->setAlignment(Qt::AlignHCenter);

  //qtextedit for name
  enterName = new QTextEdit();
    enterName->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    enterName->setFixedSize(nW, nH);

  // add everything to layout
  layout->addWidget(nameMenuLabel,1,1);
  layout->addWidget(enterName,1,2);
  layout->addWidget(nameButton,1,3);
    layout->addWidget(playButton, 2, 1);
    layout->addWidget(stopButton, 2, 2);
    layout->addWidget(resetButton, 2, 3);
    layout->setRowMinimumHeight(2, 50);
  layout->addWidget(gameView, 3, 1, 1, -1);
    layout->addWidget(name, 4, 1);
    layout->addWidget(message, 4, 2);
    layout->addWidget(score, 4, 3);
  
  // creates rocket
  points = 0;
  rocket = new Rocket(rocketPic, GAME_WINDOW_MAX_X, GAME_WINDOW_MAX_Y, rocketPic->width(), rocketPic->height(), rocketSpeed, rocketMaxLife);
  gameScene->addItem(rocket);
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

MainWindow::~MainWindow(){
  delete gameScene;
  delete gameView;
  for (int i = 0; i < thingList.size(); i++)
    delete thingList[i];
}
