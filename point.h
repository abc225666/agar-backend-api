#ifndef TARGET_H
#define TARGET_H

#include <cmath>

class Point {
public:
    double x;
    double y;
    Point(double x, double y) : x(x), y(y) {}

    double dist(std::shared_ptr<Point> other) {
        return sqrt(pow(x-other->x, 2) + pow(y-other->y, 2));
    }
    double dist2(std::shared_ptr<Point> other) {
        return pow(x-other->x, 2) + pow(y-other->y, 2);
    }
    double deg(std::shared_ptr<Point> other) {
        return atan2(other->y-y, other->x-x);
    }

    double getX() const { return x; }
    double getY() const { return y; }

    
};

#endif
