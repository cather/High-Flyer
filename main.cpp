#include <QtGui/QApplication>
#include "mainwindow.h"

/** 
  @mainpage CSCI 102 PA 5
  @section purpose Purpose
    To learn how to build a game using Qt
  @author Cathy Ji
*/



int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  
  MainWindow w;
  w.show();
  return a.exec();
  
}
