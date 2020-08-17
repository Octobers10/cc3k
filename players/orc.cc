#include "orc.h"

using namespace std;

Orc::Orc(int x, int y):
    Player{180, 30, 25, x, y} {} 


void Orc::resetPlayer() {
    atk = 30;
    def = 25;
}

bool Orc::setGold(Gold & gold) {
    if (gold.getPickable()){
        numGold += 0.5 * (double)gold.getAmount();
        return true;
    } else {
        return false;
    }
}

void Orc::incGold() {
    numGold = numGold + 0.5;
}


void Orc::consumePotion(Potion & potion){
    string type = potion.getType();
    if (type == "RH"){
        if (hp >= 170){
            hp = 180;
        } else{
            hp += 10;
        }
    }
    if (type == "BA") { atk += 5; }
    if (type == "BD") { def += 5; }
    if (type == "PH") {
        if (hp <= 10){
            hp = 0; 
            alive = false;
        } else {
            hp -= 10;
        }
    }   
    if (type == "WA"){
        if (atk <= 5){
            atk = 0; 
        } else {
            atk -= 5;
        }
    }   
    if (type == "WD"){
        if (def <= 5){
            def = 0; 
        } else {
            def -= 5;
        }
    }
}
