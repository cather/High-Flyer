#include "mainwindow.h"
using namespace std;

void MainWindow::shootLaser(int x, int y){
  if (validToShoot)
  {
    laser = new Laser(laserPic, 5, 5, rocket);
    gameScene->addItem(laser);
    thingList.push_back(laser);
    laser->shoot(x,y);
  }
}

void MainWindow::startGame() {
  enteredName = true;
  QString n = enterName->toPlainText();
  
  name->setText(n);
  nameButton->hide();
  enterName->hide();
  nameMenuLabel->hide();

  starting = false;
  rocket->show();
  rocket->setPos((GAME_WINDOW_MAX_X-(rocket->getWidth()))/2, GAME_WINDOW_MAX_Y);
  rocket->pause = false;
  rocket->grabKeyboard();

  gameTimer->start();
  playButton->setText("Pause");
  validToShoot = true;
}

void MainWindow::resetGame(){
  connect(nameButton, SIGNAL(clicked()), this, SLOT(startGame()));
  clockTime = 100;
  enteredName = false;
  nameButton->show();
    nameButton->setText("Welcome abord!");
  enterName->show();
  nameMenuLabel->show();
    nameMenuLabel->setText("Enter your name");
  starting = true;
  gameTimer->stop();
  playButton->setText("Play");
  points = 0;
  counter = 0;
  
  //delete everything
  while (!thingList.empty())
  {
    thingList.peek_front()->hide();
    thingList.pop_front();
  }
  
  //make a new rocket
  rocket = new Rocket(rocketPic, GAME_WINDOW_MAX_X, GAME_WINDOW_MAX_Y, rocketSpeed, rocketMaxLife);
  gameScene->addItem(rocket);
  rocket->setZValue(100);
  rocket->hide();
  thingList.push_back(rocket);
     
  message->setText("Health: ---  Lives: -");
  score->setText("Score: -");
}

void MainWindow::endGame(){
  
  nameButton->show();
  nameButton->setText("Fly again");
    connect(nameButton, SIGNAL(clicked()), this, SLOT(resetGame()));
  nameMenuLabel->show();
  nameMenuLabel->setText(name->text() + "'s score: " + QString::number(points) );
  while (!thingList.empty())
  {
    thingList.peek_front()->hide();
    thingList.pop_front();
  }
  validToShoot = false;
  
}

void MainWindow::triggerTimer() {

  if (enteredName)
  {
    if ( gameTimer->isActive() )
    {
      gameTimer->stop();
      playButton->setText("Play");
      rocket->pause = true;
      validToShoot = false;
    }
    else
    {
      gameTimer->start();
      playButton->setText("Pause");
      rocket->pause = false;
      validToShoot = true;
    }
  }
}

void MainWindow::handleTimer() {

    // add star every 25 ticks
  if (counter > 0 && counter % 25 == 0)
  {  
    star = new Star(starPic, rand()%GAME_WINDOW_MAX_X, rand()%GAME_WINDOW_MAX_Y);
    gameScene->addItem(star);
    thingList.push_back(star);
  }
  
  //add planet every 15 ticks
  if (counter > 0 && counter % 15 == 0)
  {  
    planet = new Planet(planetPic, 100, 0);
    gameScene->addItem(planet);
    thingList.push_back(planet);
  }
  
  // add meteor every 25 ticks
  if (counter > 0 && counter%25 == 0)
  {
    meteor = new Meteor(meteorPic, rand()%GAME_WINDOW_MAX_Y, 10);
    gameScene->addItem(meteor);
    thingList.push_back(meteor);
  }
    
  // add alien every 35 ticks
  if (counter > 0 && counter%35 == 0)
  {
    alien = new Alien(alienPic, rand()%10, rand()%200);
    gameScene->addItem(alien);
    thingList.push_back(alien);
  }
  // add missile every 25 ticks
  if (counter > 0 && counter % 15 == 0 && alien !=NULL)
  {  
    missile = new Missile(missilePic, GAME_WINDOW_MAX_X/2, 0, 5, 5, rocket);
    gameScene->addItem(missile);
    thingList.push_back(missile);
  }
  
  // move every Thing, deleting those off-screen
  thingList[0]->move(GAME_WINDOW_MAX_X, GAME_WINDOW_MAX_Y); // rocket first
  for (int i = 1; i < thingList.size(); i++)
  {
    thingList[i]->move(GAME_WINDOW_MAX_X, GAME_WINDOW_MAX_Y);
    thingList[i]->collidesWithItem(rocket); // check if touching rocket
    if(thingList[i]->offScreen)
    {
      thingList[i]->hide();
      thingList.pop(i);
      i--;
    }
  }
  
  
  gameScene->advance();
  
  // Update info
  rocket->displayHealth(message); // update health
  points = points+1+rocket->getStars(); // update score
  score->setText("Score: " + QString::number(points)); // update score
  counter++; // update timer counter
  if (rocket->getHealth() == 0)
    endGame();
    
      
  // level up every 100 ticks
  if (counter > 0 && counter % 200 == 0)
  {
    cout << "Level up"<<endl;
    clockTime += clockTime;
    gameTimer->setInterval(clockTime);
    while(1 < thingList.size())
    {
      thingList[1]->hide();
      thingList.pop(1);
    }
  }
}


MainWindow::MainWindow(){
  validToShoot = false;
  enteredName = false;
  starting = true;
  clockTime = 100;
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

  // construct layout
  layout = new QGridLayout();
  bigScene = new QGraphicsScene();
  bigView = new QGraphicsView(bigScene);
  gameScene = new ClickScene(this);
  gameView = new QGraphicsView(gameScene);
    gameScene->addPixmap(QPixmap("bg.png"));

    bigView->setLayout(layout);
    gameScene->setSceneRect(0, 0, GAME_WINDOW_MAX_X, GAME_WINDOW_MAX_Y);
    cout << GAME_WINDOW_MAX_X << " " << GAME_WINDOW_MAX_Y << endl;
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
  rocket = new Rocket(rocketPic, GAME_WINDOW_MAX_X, GAME_WINDOW_MAX_Y, rocketSpeed, rocketMaxLife);
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

