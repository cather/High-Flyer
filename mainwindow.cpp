#include "mainwindow.h"
using namespace std;

/** Adds a Missile to the screen and pushes it back to the thingList
@param AlienMidx the x coordinate to spawn the missile at
@param AlienMidy the y coordinate to spawn the missile at
*/
void MainWindow::spawnMissile(int AlienMidx, int AlienMidy){
  missile = new Missile(missilePic, AlienMidx,  AlienMidy, missilePic->width(), missilePic->height(), 20, rocket, explosion);
  gameScene->addItem(missile);
  thingList.push_back(missile);
}

/** Adds a Laser to the screen, calls the Laser's shoot function, and pushes it back to the thingList. A Laser is only spawned if validToShoot is true
@param x the x-coord to spawn the Laser at
@param y the y-coord to spawn the Laser at*/
void MainWindow::shootLaser(int x, int y){
  if (validToShoot)
  {
    laser = new Laser(laserPic, 5, 5, laserPic->width(), laserPic->height(), rocket);
    gameScene->addItem(laser);
    laser->shoot(x,y);
    thingList.push_back(laser);
  }
}

/** Function that starts the game. Updates labels and buttons to indicate game has started, starts timer, and toggles Laser spawning capability*/
void MainWindow::startGame() {
  enteredName = true;
  QString n = enterName->toPlainText();
  
  name->setText(n);
  nameButton->hide();
  enterName->hide();
  nameMenuLabel->hide();

  starting = false;
  rocket->show();
  rocket->grabKeyboard();

  gameTimer->start();
  playButton->setText("Pause");
  validToShoot = true;
}

/** Function that resets the game. Updates labels and buttons to indicate a new game is in progress, resets the the timer, clears the scene and deletes all Things, and adds a new rocket*/
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
  rocket = new Rocket(rocketPic, GAME_WINDOW_MAX_X, GAME_WINDOW_MAX_Y, rocketPic->width(), rocketPic->height(), rocketSpeed, rocketMaxLife);
  gameScene->addItem(rocket);
  rocket->hide();
  thingList.push_back(rocket);
     
  message->setText("Health: ---  Lives: -");
  score->setText("Score: -");
}

/** Function that ends the game. Updates labels and buttons to indicate a game is over. Deletes everything from the scene and displays the final score*/
void MainWindow::endGame(){  
  nameButton->show();
  nameButton->setText("Fly again");
    connect(nameButton, SIGNAL(clicked()), this, SLOT(resetGame()));
  nameMenuLabel->show();
  nameMenuLabel->setText(name->text() + "'s score: " + QString::number(points) );
  gameTimer->stop();
  while (!thingList.empty())
  {
    thingList.peek_front()->hide();
    thingList.pop_front();
  }
  validToShoot = false;
}

/** Function that triggers the gameTimer on and off. Reconfigures buttons and user-interactivity based on whether the gameTimer is on or off*/
void MainWindow::triggerTimer() {
  if (enteredName)
  {
    if ( gameTimer->isActive() )
    {
      gameTimer->stop();
      playButton->setText("Play");
      validToShoot = false;
    }
    else
    {
      gameTimer->start();
      playButton->setText("Pause");
      validToShoot = true;
    }
  }
}

/** Function that is called whenever the timer times out. Adds Items at different time intervals to the screen and to the thingList list. Moves each thing on the screen, hiding those that move offScreen or run out of health, and updates the player's health. Also increments score and displays it, as well as triggering when to level up by making gameplay faster*/
void MainWindow::handleTimer() {
    // add star every 25 ticks
  if (counter > 0 && (counter) % 10 == 0)
  {  
    star = new Star(starPic, rand()%GAME_WINDOW_MAX_X, rand()%GAME_WINDOW_MAX_Y, starPic->width(), starPic->height());
    gameScene->addItem(star);
    thingList.push_back(star);
  }
  
  
  // 
  //add planet every 15 ticks
  if (counter > 0 && (counter) % 55 == 0)
  {  
    planet = new Planet(planetPic, 0, 0, planetPic->width(), planetPic->height());
    gameScene->addItem(planet);
    thingList.push_back(planet);
  }
  
  // add meteor every 25 ticks
  if (counter > 0 && counter%25 == 0)
  {
    meteor = new Meteor(meteorPic, rand()%GAME_WINDOW_MAX_Y, meteorPic->width(), meteorPic->height(), 10);
    gameScene->addItem(meteor);
    thingList.push_back(meteor);
  }
   
  // add alien every 35 ticks
  if (counter > 0 && (counter)%35 == 0)
  {
    alien = new Alien(alienPic, alienPic->width(), alienPic->height(), 2);
    gameScene->addItem(alien);
    thingList.push_back(alien);
    spawnMissile( (alien->getWidth()-alien->getX())/2, (alien->getHeight()-alien->getY()) );
    
  }
  
  
  // move every Thing, deleting those off-screen
  for (int i = 0; i < thingList.size(); i++)
  {
    thingList[i]->move(GAME_WINDOW_MAX_X, GAME_WINDOW_MAX_Y);
    if (thingList[i]->getPic() != rocketPic && thingList[i]->getPic() != laserPic)
    {
      // check if touching rocket
      bool touchRocket = thingList[i]->collidesWith(rocket);
      
      // if not, check if touching laser
      if (!touchRocket)
      {
        for (int j = 0; j < thingList.size(); j++)
        {
          if (thingList[j]->getPic() == laserPic)
            thingList[i]->collidesWith(thingList[j]);
        }
      }
    }
    
    //if off screen or has zero health, delete
    if(thingList[i]->offScreen || thingList[i]->dead)
    {
      thingList[i]->hide();
      thingList.pop(i);
      i--;
    }
  }
  
  
  
  gameScene->advance();
  
  // Update info
  rocket->displayHealth(message); // update health
  if (counter > 0 && counter % 20 == 0)
      points++;
  if (rocket->getStars() == starPoints+1)
  {
    points = points+10; // update score
    starPoints += 1;
  }
  score->setText("Score: " + QString::number(points)); // update score
  counter++; // update timer counter
  if (rocket->getHealth() == 0)
    endGame();
    
      /*
  // level up every 100 ticks
  if (counter > 0 && counter % 200 == 0)
  {
    cout << "Level up"<<endl;
    clockTime -= 5;
    if (clockTime < 0 || clockTime == 0)
      gameTimer->stop();
    gameTimer->setInterval(clockTime);
    while(1 < thingList.size())
    {
      thingList[1]->hide();
      thingList.pop(1);
    }
  }
  */
}

/** Function that shows the QGraphicsView that encapsulates the entire program */
void MainWindow::show(){
  bigView->show();
}

/** Constructor. Creates all pixmaps, layout items, buttons, labels, and button connections. Also creates an intial Rocket item and adds it to the screen but hides it until startGame is called*/
MainWindow::MainWindow(){
  starPoints = 0;
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
  missilePic = new QPixmap("images/missile.jpg");
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
  score->setText("Score: -");
  
  // connections
  connect(gameTimer, SIGNAL(timeout()), this, SLOT(handleTimer()));
  connect(nameButton, SIGNAL(clicked()), this, SLOT(startGame()));
  connect(playButton, SIGNAL(clicked()), this, SLOT(triggerTimer()));
  connect(resetButton, SIGNAL(clicked()), this, SLOT(resetGame()));
  connect(stopButton, SIGNAL(clicked()), qApp, SLOT(quit()));

}

/** Destructor*/
MainWindow::~MainWindow(){
  delete gameScene;
  delete gameView;
  for (int i = 0; i < thingList.size(); i++)
    delete thingList[i];
}

