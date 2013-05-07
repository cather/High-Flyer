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
  playerName = nameField->toPlainText();
  if (!playerName.isEmpty()) // makes sure user has entered something in the field
  {
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
  
  scoreView->show();
  scoresVisible = true;
  
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
  
  scoreView->show();
  scoresVisible = true;
  
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
  
  // add small meteor every 10 ticks
  if (counter > 0 && counter%20 == 0)
  {
    meteor = new Meteor(meteorPic, rand()%GAME_WINDOW_MAX_Y, meteorPic->width(), meteorPic->height(), minMeteorSpeed+rand()%meteorSpeedrf);
    gameScene->addItem(meteor);
    thingList.push_back(meteor);
  }
  
  // add big meteor every 20 ticks
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
  

  // level up every 300 ticks by making timer faster
  if (counter > 0 && counter % 300 == 0)
  {
    level++;
    if (level == 2) // specs for level 2
    {
      gameScene->setBackgroundBrush(QBrush(*bg2));
      minMeteorSpeed += 5;
    }
    if (level > 2) // specs for upper levels
    {
      gameScene->setBackgroundBrush(QBrush(*bg3));
      minMeteorSpeed += 7;
      meteorSpeedrf += 5;
    }
    nameMenuLabel->setText("Level " + QString::number(level));
    message->setText("Level up");
    clockTime -= 15; // reduce time until gameTimer times out
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
  // update score for megastar points
  if (rocket->getMegastars() == starPoints+1)
  {
    points = points+50; 
    starPoints += 1;
    message->setText("Collected MEGAstar!");
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
