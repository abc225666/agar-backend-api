#ifndef GAME_H
#define GAME_H

#include <set>
#include <string>

#include "cell.h"
#include "user.h"

class Game {
public:
    std::set<std::shared_ptr<Cell>> foods;
    std::map<std::string, std::shared_ptr<User>> users;
    
    unsigned long max_foods;
    double max_x;
    double max_y;

    // create new game
    Game() : max_foods(20000), max_x(20000), max_y(20000) {
        // generate foods
        genFoods();
    }

    // add a user to the game
    void addUser(std::string username) {
        double spawn_x = max_x * rand() / (RAND_MAX+1.0);
        double spawn_y = max_y * rand() / (RAND_MAX+1.0);
        std::shared_ptr<User> user(new User(username, spawn_x, spawn_y));
        users.insert(std::make_pair(username, user));
    }

    // tick for game
    void gameTick() {

    }


private:
    void genFoods() {
        for(unsigned long i=0;i<max_foods - foods.size();i++) {
            double food_mass = rand() / (RAND_MAX+1.0) + 2;
            double spawn_x = (max_x) * rand() / (RAND_MAX+1.0);
            double spawn_y = (max_y) * rand() / (RAND_MAX+1.0);
            std::shared_ptr<Cell> food(new Cell(food_mass, spawn_x, spawn_y));
            foods.insert(food);
        }
    }

    
};

#endif
