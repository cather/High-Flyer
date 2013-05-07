#include "mainwindow.h"
using namespace std;


/** Toggles the file containing high scores*/
void MainWindow::showHighScores(){

  if (displayScores != NULL)
  {
    delete displayScores;
    displayScores = NULL;
    scoreButton->setText("Show high scores");
  }
  else
  {
    displayScores = new QGraphicsTextItem();
    QString sc = "HIGH SCORES \n        Name           Stars   Megastars    Score ";
    
    QString name;
    int stars;
    int megastars;
    int totalScore;
    
    
    /*
      QByteArray line = scoreFile->readLine();
      sc.append("\n" + line);
      displayScores->setPlainText(sc);
      scoreFile->close();
    */
    
    QTextStream stream(scoreFile);
    
    if (scoreFile->open(QIODevice::ReadWrite | QIODevice::Text))
    {
      for (int i = 0; i < 3; i++)
      {
        sc.append("\n" + QString::number(i+1) + ". "); // numbering
    
        stream >> name;
        stream >> stars;
        stream >> megastars;
        stream >> totalScore;
        
        if (!(stars == 0 && megastars == 0 && totalScore == 0))
        {
          sc.append( name + "     " + QString::number(stars) + "     " + QString::number(megastars) + "     " + QString::number(totalScore));
         }
      }
      displayScores->setPlainText(sc);
      
      scoreFile->close();
    }
    else
    {
      displayScores->setPlainText("Sorry, unable to display score");
    }

    gameScene->addItem(displayScores);
   // scoreButton->setText("Hide high scores");
  }
  
  
}


/** Constructor. Creates all pixmaps, layout items, buttons, labels, and button connections. Also creates an intial Rocket item and adds it to the screen but hides it until startGame is called*/
MainWindow::MainWindow(){
  meteorSpeedrf = 5;
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
  //scoreScene = new QGraphicsScene();
  //scoreView = new QGraphicsView(scoreScene);
    
  // buttons
  playButton = new QPushButton("Play");
    playButton->hide();
  stopButton = new QPushButton("Quit");
  resetButton = new QPushButton("Restart");
  nameButton = new QPushButton("Welcome Aboard!");
    nameButton->setGeometry((GAME_WINDOW_MAX_X-nW)/2,(GAME_WINDOW_MAX_Y)/2+nH, nW, nH);
  scoreButton = new QPushButton("High scores");
  
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
  displayScores = NULL;
  
  scoreFile = new QFile("scores.txt");
  
  /*
  QString s;
  if (scoreFile->open(QIODevice::ReadWrite | QIODevice::Text))
  {
    
    QTextStream stream(&scoreFile);
    while (!stream.atEnd())
    {
      s.append(stream.readAll());
    }
    displayScores->setPlainText(s);
    displayScores->show();
    scoreFile->close();
  }
  */
  
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
  layout->addWidget(scoreButton,5,1);
  
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
  connect(scoreButton, SIGNAL(clicked()), this, SLOT(showHighScores()));

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
    delete thingList[i];
}

