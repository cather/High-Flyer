#include "mainwindow.h"
using namespace std;

void MainWindow::shootLaser(int x, int y){
  if (validToShoot)
  {
    laser = new Laser(laserPic, 5, 5, laserPic->width(), laserPic->height(), rocket);
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
  cout << "Rocket " << rocket->getX() << " " << rocket->getY() << endl;
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
  rocket = new Rocket(rocketPic, GAME_WINDOW_MAX_X, GAME_WINDOW_MAX_Y, rocketPic->width(), rocketPic->height(), rocketSpeed, rocketMaxLife);
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
/*
    // add star every 25 ticks
  if (counter > 0 && (counter) % 50 == 0)
  {  
    star = new Star(starPic, rand()%GAME_WINDOW_MAX_X, rand()%GAME_WINDOW_MAX_Y);
    gameScene->addItem(star);
    thingList.push_back(star);
  }
  
  
  //add planet every 15 ticks
  if (counter > 0 && (counter) % 55 == 0)
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
  if (counter > 0 && (counter)%35 == 0)
  {
    alien = new Alien(alienPic, rand()%10, rand()%200);
    gameScene->addItem(alien);
    thingList.push_back(alien);
  }
  // add missile every 25 ticks
  if (counter > 0 && (counter) % 15 == 0 && alien !=NULL)
  {  
    missile = new Missile(missilePic, GAME_WINDOW_MAX_X/2, 0, 5, 5, rocket, explosion);
    gameScene->addItem(missile);
    thingList.push_back(missile);
  }
  */
  // move every Thing, deleting those off-screen
  thingList[0]->move(GAME_WINDOW_MAX_X, GAME_WINDOW_MAX_Y); // rocket first
  for (int i = 1; i < thingList.size(); i++)
  {
    thingList[i]->move(GAME_WINDOW_MAX_X, GAME_WINDOW_MAX_Y);
    thingList[i]->collidesWith(rocket); // check if touching rocket
    if(thingList[i]->dead)
    {
      thingList[i]->die();
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


void MainWindow::show(){
  bigView->show();
}


