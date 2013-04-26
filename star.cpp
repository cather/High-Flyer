#include "star.h"
using namespace std;
Star::Star(QPixmap* pic, int x, int y) : Thing(pic, x, y, 0, 0, 1) {
}

Star::Star(){
}

Star::~Star(){
}

void Star::collide(Rocket* rocket){
  if (Thing::collide(rocket))
  {
    rocket->addStar();
    //emit collected(points_);
  }
}
