#ifndef GAME_H
#define GAME_H

#include <set>
#include <string>

#include "cell.h"
#include "point.h"
#include "user.h"

class Game {
public:
    std::set<std::shared_ptr<Cell>> foods;
    std::map<std::string, std::shared_ptr<User>> users;
    
    unsigned long max_foods;
    std::shared_ptr<Point> boarder;

    // create new game
    Game() : max_foods(100000) {
        // generate foods
        boarder = std::make_shared<Point>(10000, 10000);
        genFoods();
    }

    // add a user to the game
    void addUser(std::string username) {
        double spawn_x = boarder->x * rand() / (RAND_MAX+1.0);
        double spawn_y = boarder->y * rand() / (RAND_MAX+1.0);
        std::shared_ptr<User> user(new User(username, spawn_x, spawn_y));
        users.insert(std::make_pair(username, user));
    }

    // catch a move event
    bool addMovePlayerEvent(std::string &username, double x, double y) {
        auto it = users.find(username);
        if(it!=users.end()) {
            std::shared_ptr<Point> move_target(new Point(x, y));
            it->second->addMoveEvent(move_target);
            return true;
        }
        else {
            return false;
        }
    }

    // tick for game
    void gameTick();


private:
    void genFoods() {
        unsigned long cur_size = foods.size();
        for(unsigned long i=0;i<max_foods - cur_size;i++) {
            double food_mass = rand() / (RAND_MAX+1.0) + 2;
            double spawn_x = boarder->x * rand() / (RAND_MAX+1.0);
            double spawn_y = boarder->y * rand() / (RAND_MAX+1.0);
            std::shared_ptr<Cell> food(new Cell(food_mass, spawn_x, spawn_y));
            foods.insert(food);
        }
    }

    
};

void Game::gameTick() {
    genFoods();
    for(auto user_iter=users.begin();user_iter!=users.end();user_iter++) {
        user_iter->second->tick(boarder);
    }
}

#endif
