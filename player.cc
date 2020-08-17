#include "player.h"
#include "potion.h"
#include "gold.h"
#include "enemy.h"
#include <cmath>

using namespace std;


Player::Player(int hp, int atk, int def, int x, int y):
    Character{hp, atk, def, 0, 0}, BSuit{false}, numGold{0.0} {}

Player::~Player(){}

double Player::getGold(){
    return numGold;
} 


void Player::wearBSuit(){
    BSuit = true;
}


bool Player::setGold(Gold & gold){
    if (gold.getPickable()){
        numGold += gold.getAmount();
        return true;
    } else {
        return false;
    }
}

int Player::attack(shared_ptr<Enemy> the_enemy){
    return the_enemy->attackedBy(atk);
}

int Player::attackedBy(int damage){
    int real_damage = 0;
    if (BSuit){
        real_damage = ceil(0.5 * damage * 100.0/(double)(100+def));
    } else {
        real_damage = ceil(damage * 100.0/(double)(100+def));
    }
    hp -= real_damage;
    return real_damage;
}

void Player::incGold(){
    ++numGold;
}

int potionToint(string potionType){
    if (potionType == "RH") return 0;
    if (potionType == "BA") return 1;
    if (potionType == "BD") return 2;
    if (potionType == "PH") return 3;
    if (potionType == "WA") return 4;
    if (potionType == "WD") return 5;
    
    return -1;
}

bool Player::getKnowledge(string potionType){
    int i = potionToint(potionType);
    return knowledge[i];
}

void Player::setKnowledge(string potionType){
    int i = potionToint(potionType);
    knowledge[i] = true;
}


bool Player::stealGold(){
    if (numGold <= 0){
        return false;
    } else {
        numGold -= 0.5;
        return true;
    }
}

int Player::stealHealth(){
    int stole = 0;
    if (hp <= 5){
        stole = hp;
        hp = 0;
    } else {
        hp -= 5;
        stole = 5;
    }
    return stole;
}
