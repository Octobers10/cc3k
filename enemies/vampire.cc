#include "vampire.h"

using namespace std;

Vampire::Vampire(int x, int y):
    Enemy{50, 25, 25, x, y, true} {}


int Vampire::notify(std::shared_ptr<Player>the_player, string &special) {
    int damage = Enemy::notify(the_player, special); 
    if (get_is_fighting()){
        int prob = rand() % 2; 
        if (prob){
            damage = the_player->stealHealth();
            special = special + "Vampire steals " + to_string(damage) + " HP from PC. ";
        }
    }
    return damage;
}
