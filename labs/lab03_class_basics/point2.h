#ifndef POINT2_H
#define POINT2_H

#include <string>

class Point2 {
  public:
    float DistanceBetween(Point2 a);
    int Quadrant();
    void Print();
    Point2(float a = 0.0, float b = 0.0);
  private:
    float x;
    float y;
};

#endif /*Lab03*/
