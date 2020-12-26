#ifndef CELL_H
#define CELL_H

#include <memory>

#include "point.h"
#include "util.h"

class Cell {
public:
    double mass;
    double radius;
    double speed;

    std::shared_ptr<Point> pos;

    Cell(double mass, double pos_x, double pos_y) : mass(mass) {
        speed = 6.5;
        pos = std::make_shared<Point> (pos_x, pos_y);
        radius = massToRadius(mass);
    }

    std::shared_ptr<Point> getPos() {
        return pos;
    }

    double getRadius() const {return radius;}

private:
    void eatOther(Cell &other_cell);
};

#endif
