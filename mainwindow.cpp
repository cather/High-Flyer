#include "mainwindow.h"
using namespace std;

/** Updates high scores after a game ends*/
void MainWindow::updateHighScores(){

  QString name1 = "";
  QString name2 = "";
  QString name3 = "";
  QString total1 = "";
  QString total2 = "";
  QString total3 = "";
  
  QTextStream read(scoreFile);
  QTextStream write(scoreFile);
  QString p1;
  QString p2;
  QString p3;
  
  // read info from file
  if (scoreFile->open(QIODevice::ReadOnly | QIODevice::Text))
  {
    read >> total1 >> name1 >> total2 >> name2 >> total3 >> name3;
    p1 = total1 + " " + name1;
    p2 = total2 + " " +  name2;
    p3 = total3 + " " +  name3;
    scoreFile->close();
  }
  
  // write info to file depending on score
  if (scoreFile->open(QIODevice::ReadWrite | QIODevice::Text))
  {
    // if new #1 score
    if (points > total1.toInt())
      write << points << " " << playerName << "\n" << p1 << "\n" << p2;
    // if new #2 score
    else if (points > total2.toInt()) 
      write << p1 << "\n" << points << " " << playerName << "\n" << p2;
    // if new #3 score
    else if (points > total3.toInt())
      write << p1 << "\n" << p2   << "\n" << points << " " << playerName;
     
   scoreFile->close();
   }

}

/** Toggles visibility of the high score list*/
void MainWindow::toggleHighScores(){
  if (scoresVisible)
  {
    scoreView->hide();
    scoresVisible = false;
  }
  else
  {
    QString name; 
    int totalScore;
    QTextStream stream(scoreFile);
    
    // opens file to read and display text on scre
    if (scoreFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
      scoreRank[0]->setText("");
      scoreName[0]->setText("Name");
      scoreTotal[0]->setText("SCORE");
      
      for (int i = 1; i < 4; i++)
      {
        scoreRank[i]->setText(QString::number(i) + ".");
        stream >> totalScore; 
        scoreTotal[i]->setText(QString::number(totalScore));
        stream >> name; 
        scoreName[i]->setText(name);
      }
    }
    
    // makes everything visible
    scoreFile->close();
    scoreView->show();
    scoresVisible = true;
  }
}

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
  points = 0;
  playerName = nameField->toPlainText();
  if (!playerName.isEmpty()) // makes sure user has entered something in the field
  {
    toggleHighScores(); // closes highscore view
  
    enteredName = true;
    validToShoot = true;

    scoreView->hide();
    scoresVisible = false;

    nameMenuLabel->setText("Level " + QString::number(level));
    name->setText(playerName);
    nameButton->hide();
    nameField->hide();
    message->setText("");
    playButton->show();
    playButton->setText("Pause");
    resetButton->show();

    gameTimer->start(); // start timer
  }
}

/** Function that resets the game. Updates labels and buttons to indicate a new game can be started, resets the the timer, clears the scene and deletes all Things, and adds a new rocket*/
void MainWindow::resetGame(){
  
  validToShoot = false;
  gameTimer->stop();
  
  toggleHighScores(); // closes highscore view
  
  connect(nameButton, SIGNAL(clicked()), this, SLOT(startGame()));
  clockTime = 100; // reset length of timer
  gameTimer->setInterval(clockTime);
  
  enteredName = false;
  nameButton->show();
    nameButton->setText("Welcome abord!");
  nameField->show();
  nameMenuLabel->show();
    nameMenuLabel->setText("Enter your name: ");
  
  playButton->hide();
  playButton->setText("Play");
  resetButton->hide();
  
  gameTimer->stop();
  points = 0;
  counter = 0;
  
  //delete everything
  while (!thingList.empty())
  {
    thingList.peek_front()->hide();
    thingList.pop_front();
  }
  thingList.clear();
  
  //make a new rocket
  rocket = new Rocket(rocketPic, GAME_WINDOW_MAX_X, GAME_WINDOW_MAX_Y, rocketPic->width(), rocketPic->height(), rocketSpeed/level, rocketMaxLife);
  gameScene->addItem(rocket);
  rocket->grabKeyboard();
  thingList.push_back(rocket);
     
  level = 1; // reset level
  score->setText("Score: -");
}

/** Function that ends the game. Updates labels and buttons to indicate a game is over. Deletes everything from the scene and displays the final score information*/
void MainWindow::endGame(){  
  gameTimer->stop();
  validToShoot = false;
  
  nameMenuLabel->show();
  nameMenuLabel->setText("Great flight " + name->text() + "! Stars: " + QString::number(starPoints));
  nameButton->show();
  nameButton->setText("Fly again");
    connect(nameButton, SIGNAL(clicked()), this, SLOT(resetGame()));
  playButton->hide();
  resetButton->hide();
  
  message->setText("Game Over");

  // delete everything
  while (!thingList.empty())
  {
    thingList.peek_front()->hide();
    thingList.pop_front();
  }
  thingList.clear();
  
 updateHighScores();  
 toggleHighScores(); // opens highscore view
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
    
    toggleHighScores();
  }
}

/** Function that is called whenever the timer times out. Adds Items at different time intervals to the screen and to the thingList list. Moves each thing on the screen, hiding those that move offScreen or run out of health, and updates the player's health. Also increments score and displays it, as well as triggering when to level up by making gameplay faster*/
void MainWindow::handleTimer() {

    // add star every 50 ticks
  if (counter > 0 && (counter) % 50 == 0)
  {  
    star = new Star(starPic, rand()%GAME_WINDOW_MAX_X/level, -starPic->height(), starPic->width(), starPic->height(),5/level, 10/level);
    gameScene->addItem(star);
    thingList.push_back(star);
  }
  
  // add megastar every 100 ticks
  if (counter > 0 && counter % 100 == 0)
  {
    megastar = new Megastar(megastarPic, rand()%GAME_WINDOW_MAX_X/level, 0, megastarPic->width(), megastarPic->height(), 3, rocket);
    gameScene->addItem(megastar);
    thingList.push_back(megastar);
  }
  
  //add planet every 60 ticks
  if (counter > 0 && (counter) % 60 == 0)
  {  
    planet = new Planet(planetPic, rand()%GAME_WINDOW_MAX_X, 0, planetPic->width(), planetPic->height());
    gameScene->addItem(planet);
    thingList.push_back(planet);
  }
  
  // add small meteor every 15 ticks
  if (counter > 0 && counter%15 == 0)
  {
    meteor = new Meteor(meteorPic, rand()%GAME_WINDOW_MAX_Y, meteorPic->width(), meteorPic->height(), minMeteorSpeed+rand()%meteorSpeedrf);
    gameScene->addItem(meteor);
    thingList.push_back(meteor);
  }
  
  // add big meteor every 30 ticks
  if (counter > 0 && counter%30 == 0)
  {
    meteor = new Meteor(meteorBigPic, rand()%GAME_WINDOW_MAX_Y, meteorPic->width(), meteorPic->height(), minMeteorSpeed+rand()%meteorSpeedrf);
    gameScene->addItem(meteor);
    thingList.push_back(meteor);
  }
   
  // add alien every 45 ticks after level 1
  if (counter > 0 && (counter)%45 == 0 && level > 1)
  {
    alien = new Alien(alienPic, alienPic->width(), alienPic->height(), 40);
    gameScene->addItem(alien);
    thingList.push_back(alien);
  
    // aliens shoot missiles after level 2
    if (level > 2)
      spawnMissile( (alien->getWidth()-alien->getX())/2, (alien->getHeight()-alien->getY()) );
  }
  
  // move every Thing, deleting those off-screen
  for (int i = 0; i < thingList.size(); i++)
  {
    thingList[i]->move(GAME_WINDOW_MAX_X, GAME_WINDOW_MAX_Y);
    
    //check for collisions with rocket or laser
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
  

  // level up every 150 ticks by making timer faster
  if (counter > 0 && counter % 150 == 0)
  {
    level++;
    if (level == 2) // specs for level 2
    {
      gameScene->setBackgroundBrush(QBrush(*bg2));
      minMeteorSpeed += 10;
    }
    if (level > 2) // specs for upper levels
    {
      gameScene->setBackgroundBrush(QBrush(*bg3));
      minMeteorSpeed += 5;
      meteorSpeedrf += 7;
    }
    nameMenuLabel->setText("Level " + QString::number(level));
    message->setText("Level up");
    clockTime -= 15; // reduce time until gameTimer times out
    if (clockTime < 0 || clockTime == 0)
    {
      clockTime = 0;
      gameTimer->stop();
      message->setText("You won!");
      endGame();
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
    starPoints += 1;
    if (rocket->getMegastars() == starPoints+1)
    {
      points = points+50; 
      message->setText("Collected MEGAstar!");
    }
    else
    {
      points = points+10; 
      message->setText("Collected star!");
    }
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
  meteorSpeedrf = 15;
  minMeteorSpeed = 7;
  level = 1;
  starPoints = 0;
  validToShoot = false;
  enteredName = false;
  clockTime = 100;
  counter = 0;
  int nW = 200, nH = 25; // w/h variables for name elements
  
  // storing graphics  
  rocketPic = new QPixmap("images/rocket.png");
  planetPic = new QPixmap("images/planet.png");
  starPic = new QPixmap("images/star.png");
  missilePic = new QPixmap("images/missile.png");
  alienPic = new QPixmap("images/alien.png");
  laserPic = new QPixmap("images/laser.jpg");
  meteorPic = new QPixmap("images/meteor_small.png");
  meteorBigPic = new QPixmap("images/meteor.png");
  megastarPic = new QPixmap("images/megastar.png");
  bg1 = new QImage("images/bg_fabric.png");
  bg2 = new QImage("images/bg_dots.png");
  bg3 = new QImage("images/bg_lines.png");

  // construct layout
  layout = new QGridLayout();
  bigScene = new QGraphicsScene();
  bigView = new QGraphicsView(bigScene);
  gameScene = new ClickScene(this);
  gameView = new QGraphicsView(gameScene);
    bigView->setLayout(layout);
    gameScene->setSceneRect(0, 0, GAME_WINDOW_MAX_X, GAME_WINDOW_MAX_Y);
    gameView->setFixedSize(BIG_WINDOW_MAX_X, BIG_WINDOW_MAX_Y);
    gameScene->setBackgroundBrush(QBrush(*bg1));
  
  //for high scores
  scoreFile = new QFile("scores.txt");
  
  highscoretablelayout = new QGridLayout();
  scoreScene = new QGraphicsScene();
  scoreView = new QGraphicsView(scoreScene);
  scoreView->setLayout(highscoretablelayout);
  scoreScene->setSceneRect(200, BIG_WINDOW_MAX_Y/2, 500, BIG_WINDOW_MAX_Y/4);
  scoreView->setFixedSize(300, 100);
    scoreView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scoreView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  scoresVisible = false;

   highscoretabletitle = new QLabel("HIGH SCORES");
   highscoretablelayout->addWidget(highscoretabletitle,0,1,1,-1);
   

  // create all labels needed to display high scores nad add them to layout
  for (int i = 1; i < 5; i++)
  {
    QLabel* rank = new QLabel();
    QLabel* nm = new QLabel();
    QLabel* tot = new QLabel();
    
    scoreRank.push_back(rank);
    scoreName.push_back(nm);
    scoreTotal.push_back(tot);
    
    highscoretablelayout->addWidget(scoreRank[i],i,1);
    highscoretablelayout->addWidget(scoreName[i],i,2);
    highscoretablelayout->addWidget(scoreTotal[i],i,3);
  }
  
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
  health = new QLabel("Health: ---  Lives: -");
  score = new QLabel("Score: -");
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
  layout->addWidget(scoreView, 3, 1, 1, -1);
  scoreView->hide();
    layout->addWidget(message, 4, 1);
    layout->addWidget(health, 4, 2);
    layout->addWidget(score, 4, 3);
  
  updateHighScores(); // open high score view
  toggleHighScores(); // turn on high score view
  
  // creates rocket
  points = 0;
  rocket = new Rocket(rocketPic, GAME_WINDOW_MAX_X, GAME_WINDOW_MAX_Y, rocketPic->width(), rocketPic->height(), rocketSpeed/level, rocketMaxLife);
  gameScene->addItem(rocket);
  rocket->grabKeyboard(); // rocket responds to keyboard
  thingList.push_back(rocket);
  
  // connections
  connect(gameTimer, SIGNAL(timeout()), this, SLOT(handleTimer()));
  connect(nameButton, SIGNAL(clicked()), this, SLOT(startGame()));
  connect(playButton, SIGNAL(clicked()), this, SLOT(triggerTimer()));
  connect(resetButton, SIGNAL(clicked()), this, SLOT(resetGame()));
  connect(stopButton, SIGNAL(clicked()), qApp, SLOT(quit()));

}

/** Destructor*/
MainWindow::~MainWindow(){
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
  {
    delete thingList[i];
  }
}
