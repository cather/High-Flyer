#include "mainwindow.h"
using namespace std;

/** Updates high scores after a game ends*/
void MainWindow::updateHighScores(){
  //scoreView->show();
  QString name;
  int stars;
  int totalScore;
  QTextStream out(scoreFile);
  QTextStream in(scoreFile);
  QString p1;
  QString p2;
  QString p3;
  
  if (scoreFile->open(QIODevice::ReadOnly | QIODevice::Text))
  {
    p1 = out.readLine();
    p2 = out.readLine();
    p3 = out.readLine();
  }
  scoreFile->close();
  
  scoreFile2 = new QFile("scores2.txt");
  if (scoreFile2->open(QIODevice::ReadWrite | QIODevice::Text))
  {
    QTextStream readData(scoreFile2);
    readData >> name; 
    readData >> stars; 
    readData >> totalScore; 
    
    if (points > totalScore)
    {
      in << playerName << " " << starPoints << " " << points << "\n";
      in << p1 << "\n";
      in << p2 << "\n";
    }
   }
   scoreFile2->close();
   
   scoreFile2->rename("scores2.txt", "scores.txt");
   
  
}


/** Toggles the file containing high scores*/
void MainWindow::toggleHighScores(){
  if (scoresVisible)
  {
    scoreView->hide();
    scoresVisible = false;
  }
  else
  {
    scoreView->show();
    QString name;
    int stars;
    int totalScore;
    QTextStream stream(scoreFile);
    if (scoreFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
      scoreRank[0]->setText("");
      scoreName[0]->setText("Name");
      scoreStars[0]->setText("Stars");
      scoreTotal[0]->setText("TOTAL SCORE");
      for (int i = 1; i < 4; i++)
      {
        scoreRank[i]->setText(QString::number(i) + ".");
        stream >> name; 
        scoreName[i]->setText(name);
        stream >> stars;
        scoreStars[i]->setText(QString::number(stars));
        stream >> totalScore; 
        scoreTotal[i]->setText(QString::number(totalScore));
        if (totalScore == 0)
        {
          scoreName[i]->hide();
          scoreStars[i]->hide();
          scoreTotal[i]->hide();
        }
        else
        {
          scoreName[i]->show();
          scoreStars[i]->show();
          scoreTotal[i]->show();
        }
      }
      scoreFile->close();
    }
   scoresVisible = true;
  }
}

/** Constructor. Creates all pixmaps, layout items, buttons, labels, and button connections. Also creates an intial Rocket item and adds it to the screen but hides it until startGame is called*/
MainWindow::MainWindow(){
  meteorSpeedrf = 10;
  minMeteorSpeed = 5;
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

   QLabel* highscoretabletitle = new QLabel("HIGH SCORES");
   highscoretablelayout->addWidget(highscoretabletitle,0,1,1,-1);
   

  for (int i = 1; i < 5; i++)
  {
    QLabel* rank = new QLabel();
    QLabel* nm = new QLabel();
    QLabel* strs = new QLabel();
    QLabel* tot = new QLabel();
    
    scoreRank.push_back(rank);
    scoreName.push_back(nm);
    scoreStars.push_back(strs);
    scoreTotal.push_back(tot);
    
    highscoretablelayout->addWidget(scoreRank[i],i,1);
    highscoretablelayout->addWidget(scoreName[i],i,2);
    highscoretablelayout->addWidget(scoreStars[i],i,3);
    highscoretablelayout->addWidget(scoreTotal[i],i,4);
  }
  updateHighScores(); // open high score view

  
  
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
  
 // delete highscoretabletitle;
  
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
