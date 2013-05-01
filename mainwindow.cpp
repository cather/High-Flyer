#include "mainwindow.h"
using namespace std;

/** Adds a Missile to the screen and pushes it back to the thingList
  @param AlienMidx the x coordinate to spawn the missile at
  @param AlienMidy the y coordinate to spawn the missile at
*/
void MainWindow::spawnMissile(int AlienMidx, int AlienMidy){
  missile = new Missile(missilePic, AlienMidx,  AlienMidy, missilePic->width(), missilePic->height(), 2, rocket);
  gameScene->addItem(missile);
  thingList.push_back(missile);
}

/** Adds a Laser to the screen, calls the Laser's shoot function, and pushes it back to the thingList. A Laser is only spawned if validToShoot is true
  @param x the x-coord to spawn the Laser at
  @param y the y-coord to spawn the Laser at
*/
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
  level = 1;
  QString n = nameField->toPlainText();
  if (!n.isEmpty())
  {
    enteredName = true;
    nameMenuLabel->setText("Level " + QString::number(level));
    name->setText(n);
    nameButton->hide();
    nameField->hide();
    message->setText("");
    
    playButton->show();
    resetButton->show();

    starting = false;
    gameTimer->start();
    rocket->show();
    rocket->grabKeyboard();
    
    playButton->setText("Pause");
    validToShoot = true;
  }
}

/** Function that resets the game. Updates labels and buttons to indicate a new game is in progress, resets the the timer, clears the scene and deletes all Things, and adds a new rocket*/
void MainWindow::resetGame(){
  
  validToShoot = false;
  rocket->ungrabKeyboard();
  gameTimer->stop();
  
  connect(nameButton, SIGNAL(clicked()), this, SLOT(startGame()));
  clockTime = 100;
  gameTimer->setInterval(clockTime);
  
  enteredName = false;
  nameButton->show();
    nameButton->setText("Welcome abord!");
  nameField->show();
  nameMenuLabel->show();
    nameMenuLabel->setText("Enter your name: ");
  starting = true;
  
  playButton->hide();
  resetButton->hide();
  
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
     
  level = 1;
  //message->setText("Level " + QString::number(level));
  score->setText("Score: -");
}

/** Function that ends the game. Updates labels and buttons to indicate a game is over. Deletes everything from the scene and displays the final score*/
void MainWindow::endGame(){  
  gameTimer->stop();
  validToShoot = false;
//  rocket->ungrabKeyboard();

  nameMenuLabel->show();
  nameMenuLabel->setText("Great flight " + name->text() + "! Stars: " + QString::number(starPoints));

  nameButton->show();
  nameButton->setText("Fly again");
    connect(nameButton, SIGNAL(clicked()), this, SLOT(resetGame()));
  playButton->hide();
  resetButton->hide();
  
  message->setText("Game Over");


  while (!thingList.empty())
  {
    thingList.peek_front()->hide();
    thingList.pop_front();
  }
  thingList.clear();
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
      rocket->ungrabKeyboard();
    }
    else
    {
      gameTimer->start();
      playButton->setText("Pause");
      validToShoot = true;
      rocket->grabKeyboard();
    }
  }
}

/** Function that is called whenever the timer times out. Adds Items at different time intervals to the screen and to the thingList list. Moves each thing on the screen, hiding those that move offScreen or run out of health, and updates the player's health. Also increments score and displays it, as well as triggering when to level up by making gameplay faster*/
void MainWindow::handleTimer() {

    // add star every 50 ticks
  if (counter > 0 && (counter) % 50 == 0)
  {  
    star = new Star(starPic, rand()%GAME_WINDOW_MAX_X, 0, starPic->width(), starPic->height());
    gameScene->addItem(star);
    thingList.push_back(star);
  }
  
  //add planet every 60 ticks
  if (counter > 0 && (counter) % 60 == 0)
  {  
    planet = new Planet(planetPic, rand()%GAME_WINDOW_MAX_X, 0, planetPic->width(), planetPic->height());
    gameScene->addItem(planet);
    thingList.push_back(planet);
  }
  
  // add small meteor every 10 ticks
  if (counter > 0 && counter%10 == 0)
  {
    meteor = new Meteor(meteorPic, rand()%GAME_WINDOW_MAX_Y, meteorPic->width(), meteorPic->height(), rand()%50);
    gameScene->addItem(meteor);
    thingList.push_back(meteor);
  }
  
  // add big meteor every 20 ticks
  if (counter > 0 && counter%20 == 0)
  {
    meteor = new Meteor(meteorBigPic, rand()%GAME_WINDOW_MAX_Y, meteorPic->width(), meteorPic->height(), rand()%50);
    gameScene->addItem(meteor);
    thingList.push_back(meteor);
  }
   
  // add alien every 45 ticks
  if (counter > 0 && (counter)%45 == 0)
  {
    alien = new Alien(alienPic, alienPic->width(), alienPic->height(), 55);
    gameScene->addItem(alien);
    thingList.push_back(alien);
    spawnMissile( (alien->getWidth()-alien->getX())/2, (alien->getHeight()-alien->getY()) );  //add missile
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
  
//  gameScene->advance();

  // level up every 200 ticks by making game pass faster
  if (counter > 0 && counter % 200 == 0)
  {
    level++;
    nameMenuLabel->setText("Level " + QString::number(level));
    message->setText("Level up");
    clockTime -= 15;
    if (clockTime < 0 || clockTime == 0)
    {
      gameTimer->stop();
      message->setText("You won!");
    }
    gameTimer->setInterval(clockTime);
    
    // delete everything from screen except rocket
    while(1 < thingList.size())
    {
      thingList[1]->hide();
      thingList.pop(1);
    }
  }

  // update health
  rocket->displayHealth(health); 
  // update regular points based on timer
  if (counter > 0 && counter % 20 == 0)
      points++;
  // update score for star points
  if (rocket->getStars() == starPoints+1)
  {
    points = points+10; 
    starPoints += 1;
    message->setText("Collected star!");
  }
  else
  {
    if (counter > 0 && counter % 25 == 0)
      message->setText("");
  }
  score->setText("Score: " + QString::number(points));
  counter++; // update timer counter
  
  // check if player still alive. if not, endgame
  if (rocket->getHealth() == 0 && rocket->getLives() == 0)
    endGame();
}

/** Function that shows the QGraphicsView that encapsulates the entire program */
void MainWindow::show(){
  bigView->show();
}

/** Constructor. Creates all pixmaps, layout items, buttons, labels, and button connections. Also creates an intial Rocket item and adds it to the screen but hides it until startGame is called*/
MainWindow::MainWindow(){
  level = 1;
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
  missilePic = new QPixmap("images/missile.png");
  alienPic = new QPixmap("images/alien.png");
  laserPic = new QPixmap("images/laser.jpg");
  meteorPic = new QPixmap("images/meteor_small.png");
  meteorBigPic = new QPixmap("images/meteor.png");

  // construct layout
  layout = new QGridLayout();
  bigScene = new QGraphicsScene();
  bigView = new QGraphicsView(bigScene);
  gameScene = new ClickScene(this);
  gameView = new QGraphicsView(gameScene);
    gameScene->addPixmap(QPixmap("bg.png"));
    bigView->setLayout(layout);
    gameScene->setSceneRect(0, 0, GAME_WINDOW_MAX_X, GAME_WINDOW_MAX_Y);
    gameView->setFixedSize(BIG_WINDOW_MAX_X, BIG_WINDOW_MAX_Y);
    
  // buttons
  playButton = new QPushButton("Play");
    playButton->hide();
  stopButton = new QPushButton("Quit");
  resetButton = new QPushButton("Restart");
  nameButton = new QPushButton("Welcome Aboard!");
    nameButton->setGeometry((GAME_WINDOW_MAX_X-nW)/2,(GAME_WINDOW_MAX_Y)/2+nH, nW, nH);
  
  // Timer to keep track of score, health, etc
  gameTimer = new QTimer(this);
  gameTimer->setInterval(clockTime);

  // qlabel for displaying health and lives
  message = new QLabel();
  health = new QLabel();
  score = new QLabel();
  name = new QLabel();
  nameMenuLabel = new QLabel("Enter your name:");
    nameMenuLabel->setFixedSize( nW, nH);
    nameMenuLabel->setAlignment(Qt::AlignHCenter);

  //qtextedit for name
  nameField = new QTextEdit();
    nameField->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    nameField->setFixedSize(nW, nH);

  // add everything to layout
  layout->addWidget(nameMenuLabel,1,1);
  layout->addWidget(nameField,1,2);
  layout->addWidget(nameButton,1,3);
    layout->addWidget(playButton, 2, 1);
    layout->addWidget(stopButton, 2, 2);
    layout->addWidget(resetButton, 2, 3);
    layout->setRowMinimumHeight(2, 50);
  layout->addWidget(gameView, 3, 1, 1, -1);
    layout->addWidget(message, 4, 1);
    layout->addWidget(health, 4, 2);
    layout->addWidget(score, 4, 3);
  
  // creates rocket
  points = 0;
  rocket = new Rocket(rocketPic, GAME_WINDOW_MAX_X, GAME_WINDOW_MAX_Y, rocketPic->width(), rocketPic->height(), rocketSpeed, rocketMaxLife);
  gameScene->addItem(rocket);
  rocket->hide(); // hide until game starts
  thingList.push_back(rocket);
  health->setText("Health: ---  Lives: -");
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
  //delete gameScene;
  //delete gameView;
  delete bigView;
  delete bigScene;
  
  delete rocketPic;
  delete planetPic;
  delete starPic;
  delete missilePic;
  delete alienPic;
  delete laserPic;
  delete meteorPic;
  delete meteorBigPic;
  for (int i = 0; i < thingList.size(); i++)
    delete thingList[i];
}

