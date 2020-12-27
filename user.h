#ifndef USER_H
#define USER_H

#include <cmath>
#include <queue>
#include <set>
#include <string>

#include <iostream>

#include "cell.h"
#include "event.h"
#include "point.h"


class User {
public:
    std::string username;
    std::set<std::shared_ptr<Cell>> cells;
    std::shared_ptr<Point> pos;
    std::queue<std::shared_ptr<Event>> events;

    User(std::string &username, double x, double y) : username(username) {
        std::shared_ptr<Cell> start_cell(new Cell(10, x, y));
       
        cells.insert(start_cell); 
        pos = std::make_shared<Point>(x, y);
    }

    std::shared_ptr<Point> getPos() {return pos;}

    void  movePlayer(std::shared_ptr<Point> target, std::shared_ptr<Point> boarder) {
        double total_x = 0, total_y = 0; 
        
        for(auto it=cells.begin();it!=cells.end();it++) {
            double deg = (*it)->pos->deg(target);
            double slow_down = 1;
            if((*it)->speed <= 6.5) {
                slow_down= log10((*it)->speed) + 1;
            }
            else {
                (*it)->speed -= 0.5;
            }

            double deltaX = (*it)->speed * cos(deg) / slow_down;
            double deltaY = (*it)->speed * sin(deg) / slow_down;


            (*it)->pos->x += deltaX;
            (*it)->pos->y += deltaY;
            double boarder_center = (*it)->radius;

            if((*it)->pos->x > boarder->x - boarder_center) {
                (*it)->pos->x = boarder->x - boarder_center;
            }
            if((*it)->pos->y > boarder->y - boarder_center) {
                (*it)->pos->y = boarder->y - boarder_center;
            }
            if((*it)->pos->x < boarder_center) {
                (*it)->pos->x = boarder_center;
            }
            if((*it)->pos->y < boarder_center) {
                (*it)->pos->y = boarder_center;
            }

            total_x += (*it)->pos->x;
            total_y += (*it)->pos->y;
        }
        pos->x = total_x / cells.size();
        pos->y = total_y / cells.size();
    }

    void tick(std::shared_ptr<Point> boarder);
    void addMoveEvent(std::shared_ptr<Point> target);

    bool eatFood(std::shared_ptr<Cell> food);
    bool eatPlayer(std::shared_ptr<User> u);
};

void User::tick(std::shared_ptr<Point> boarder) {
    while(!events.empty()) {
        if(events.front()->event_type == EventType::Move) {
            movePlayer(events.front()->move_target, boarder);
        }
        events.pop();
    }
}

void User::addMoveEvent(std::shared_ptr<Point> target) {
    std::shared_ptr<Event> new_event(new Event(EventType::Move, target));
    events.push(new_event);
}

bool User::eatFood(std::shared_ptr<Cell> food) {
    for(auto cell_iter=cells.begin();cell_iter!=cells.end();cell_iter++) {
        double food_dist2 = (*cell_iter)->pos->dist2(food->pos);
        if(pow((*cell_iter)->radius, 2) > food_dist2) {
            double new_mass = food->mass + (*cell_iter)->mass;
            (*cell_iter)->setRadius(new_mass);
            return true;
        }
    }
    return false;
}

bool User::eatPlayer(std::shared_ptr<User> u) {
    auto my_cell = cells.begin();
    auto other_cell = u->cells.begin();

    if((*my_cell)->mass > (*other_cell)->mass * 1.1
            && (*my_cell)->radius > (*my_cell)->pos->dist((*other_cell)->pos)) {
        //eat!
        double new_mass = (*my_cell)->mass + (*other_cell)->mass;
        (*my_cell)->setRadius(new_mass);
        return true;
    }
    return false;
}

#endif
