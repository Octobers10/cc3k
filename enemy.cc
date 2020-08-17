#include "enemy.h"
#include <cstdlib>
#include <cmath>

//modified
using namespace std;

Enemy::Enemy(int hp, int atk, int def, int x, int y, bool hostile, bool dragon, bool merchant):
    Character{hp, atk, def, x, y}, hostile{hostile}, has_compass{false}, is_fighting{false}, dragon{dragon}, merchant{merchant} {}

Enemy::~Enemy(){}

void Enemy::setHostile(bool host){
    hostile = host;
}

bool Enemy::getHostile(){
    return hostile;
}

//the damage received does not consider the defenser's defense
int Enemy::attackedBy(int atkr_atk){
    int damage = ceil(atkr_atk * 100.0/(double)(100+def));
    hp -= damage;
    return damage;
}

int Enemy::attack(std::shared_ptr<Player> the_player){
    return the_player->attackedBy(atk);
}

bool Enemy::get_has_compass(){
    return has_compass;
}
void Enemy::set_has_compass(bool compass){
    has_compass = compass;
}

void Enemy::start_fighting(){
    is_fighting = true;
}

void Enemy::stop_fighting(){
    is_fighting = false;
}

int Enemy::notify(shared_ptr<Player> the_player, string & special){
    int damage= 0;
    int not_fighting = -10;
    int fight_missed = 0; 
    int just_start_fighting = -5;

    //not hostile
    if (! hostile) return not_fighting;

    std::pair<int, int> player_position = the_player->getPosition();
    int diff_first = abs(player_position.first - position.first);
    int diff_second = abs(player_position.second - position.second);
    if ((diff_first <= 1) && (diff_second <= 1)){
    //just start fighting, let player attack first
            if (! is_fighting){
                start_fighting(); 
                return just_start_fighting;
            }
    //already fighting
            int chance = rand()%2;
            //attack missed
            if (chance == 0) return fight_missed; 
            //attack not missed
            damage = this->attack(the_player);
            return damage;
    } else {
    //player is not in range
        stop_fighting();
    }
    return not_fighting;
}

void Enemy::notify_merchant(){
    return;
}


bool Enemy::isDragon(){
    return dragon; 
}

bool Enemy::get_is_fighting(){
	return is_fighting;
}


std::shared_ptr<Item> Enemy::get_item_ptr(){
	return nullptr;
}

bool Enemy::isMerchant(){
    return merchant; 
}
