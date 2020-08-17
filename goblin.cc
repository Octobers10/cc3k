#include "goblin.h"
#include <ctime>
#include <cstdlib>

using namespace std;

Goblin::Goblin(int x, int y):
    Enemy{70, 5, 10, x, y, true} {}



int Goblin::notify(std::shared_ptr<Player>the_player, string &special) {
    if (get_is_fighting()){
        int prob = rand() % 2; 
        if (prob){
            bool succeed = the_player->stealGold();
            if (succeed){
                special = special + "Goblin steals 0.5 gold from PC. ";
            }
        }
    }
    return Enemy::notify(the_player, special); 
}


