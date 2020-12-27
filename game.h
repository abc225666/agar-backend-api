#ifndef GAME_H
#define GAME_H

#include <iostream>
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
    Game() : max_foods(1000) {
        // generate foods
        boarder = std::make_shared<Point>(5000, 5000);
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

    void eatFood(std::shared_ptr<User>);
    
};

void Game::gameTick() {
    std::set<std::string> eatenPlayer;
    for(auto user_iter=users.begin();user_iter!=users.end();user_iter++) {
        if(eatenPlayer.find(user_iter->first) != eatenPlayer.end()) {
            continue;
        }
        user_iter->second->tick(boarder);
        eatFood(user_iter->second);

        // eat player check
        for(auto eat_it=users.begin();eat_it!=users.end();eat_it++) {
            if(eatenPlayer.find(eat_it->first) != eatenPlayer.end()) {
                continue;
            }
            bool eaten = user_iter->second->eatPlayer(eat_it->second);
            if(eaten) {
                eatenPlayer.insert(eat_it->first);
            }
        }
    }
    for(auto it=eatenPlayer.begin();it!=eatenPlayer.end();it++) {
        users.erase(*it);
    }
    genFoods();
}

void Game::eatFood(std::shared_ptr<User> u) {
    std::vector<std::shared_ptr<Cell>> eatenFood;
    for(auto food_iter=foods.begin();food_iter!=foods.end();food_iter++) {
        bool eaten = u->eatFood(*food_iter);
        if(eaten) {
            eatenFood.push_back(*food_iter);
        }
    }

    for(auto it=eatenFood.begin();it!=eatenFood.end();it++) {
        foods.erase(*it);
    }
}

#endif
