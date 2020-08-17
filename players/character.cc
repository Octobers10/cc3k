#include "character.h"
#include "../direction.h"

using namespace std;

Character::Character(int hp, int atk, int def, int x, int y):
    hp{hp}, atk{atk}, def{def}, position{make_pair(x,y)}, alive{true} {}

Character::~Character(){}

int Character::getHP(){
    return hp;
}

int Character::getAtk(){
    return atk;
}

int Character::getDef(){
    return def;
}

bool Character::isAlive(){
    return alive; 
}

std::pair<int, int> Character::getPosition(){
    return position; 
}

void Character::move(Direction d){
    switch(d){
        case(no): position.first = position.first - 1; 
        break;
        case(so): position.first = position.first + 1; 
        break;
        case(we): position.second = position.second - 1;
        break;
        case(ea): position.second = position.second + 1;
        break;
        case(nw): {
            position.first = position.first - 1;
            position.second = position.second - 1;
        } 
        break;
        case(ne): {
            position.first = position.first - 1; 
            position.second = position.second + 1; 
        }
        break;
        case(sw): {
            position.first = position.first + 1;
            position.second = position.second - 1; 
        }
        break;
        case(se): {
            position.first = position.first + 1;
            position.second = position.second + 1;
        }
        break;
    }
}

void Character:: setPosition(int x, int y){
    position.first = x;
    position.second = y;
}
