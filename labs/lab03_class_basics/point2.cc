#include <cmath>
#include <iostream>
using namespace std;

#include "point2.h"

Point2::Point2 (float a, float b){
  this->x = a;
  this->y = b;
}

float Point2::DistanceBetween(Point2 a){
  float result;
  float iner = pow (a.x - this->x, 2.0) + pow(a.y - this->y, 2.0);
  result = sqrt(iner);
  return result;
}

int Point2::Quadrant(){
  if (this->x > 0 && this->y >= 0){
    return 1;
  }else if (this->x <= 0 && this->y > 0){
    return 2;
  }else if (this->x < 0 && this->y <= 0){
    return 3;
  }else if (this->x >= 0 && this->y < 0){
    return 4;
  }else {
    return 0;
  }
}

void Point2::Print(){
  cout<< "("<< this->x << ", " << this->y << ")";
}
