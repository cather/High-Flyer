#include "star.h"
using namespace std;
Star::Star(QPixmap* pic, int x, int y) : Thing(pic, x, y, 0, 0, 1) {
}

Star::Star(){
}

Star::~Star(){
}

bool Star::collidesWith(Thing* rocket){
  if (collidesWithItem(rocket, Qt::IntersectsItemShape))
      emit collected(); // emits signal when touching item
  return collidesWithItem(rocket, Qt::IntersectsItemShape);
}

void Star::collected(){}
