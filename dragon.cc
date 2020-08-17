#include "dragon.h"
#include <utility>


using namespace std;

Dragon::Dragon(int x, int y, std::shared_ptr<Item> item_ptr):
    Enemy{150, 20, 20, x, y, false, true, false}, item_ptr {item_ptr} {}


shared_ptr<Item> Dragon::get_item_ptr(){
    return item_ptr;
}

int Dragon::notify(std::shared_ptr<Player>the_player, string & special) {
    pair<int,int> player_position = the_player->getPosition();
    pair<int,int> item_position = item_ptr->getPosition();

    int diff_first = abs(item_position.first - player_position.first);
    int diff_second = abs(item_position.second - player_position.second);
    if (( diff_first<= 1) && (diff_second <= 1)){
        setHostile(true);
    } else {
        setHostile(false);
    }
    int damage = Enemy::notify(the_player, special);
    return damage; 
}
