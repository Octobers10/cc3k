#include "troll.h"

using namespace std;

Troll::Troll(int x, int y):
    Enemy{120, 25, 15, x, y, true} {}

int Troll::notify(shared_ptr<Player> the_player, std::string & special){
    int restore = 0;
    if (hp < 120){
        int prob = rand() % 3; 
        if (prob == 0){
            if (hp > 115){
                restore = 120 - hp;
                special = special + "Troll restores " + to_string(restore) + " ph. ";
                hp = 120;
            } else {
                restore = 5;
                special = special + "Troll restores " + to_string(restore) + " ph. ";
                hp += 5;
            }
        }
    }
    return Enemy::notify(the_player, special); 
}
