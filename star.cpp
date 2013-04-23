#include "star.h"

Star::Star(){
  QGraphicsPixmapItem* pic = new QGraphicsPixmapItem(QPixmap("star.png"));
  setPic(pic);
}

Star::~Star(){
}

