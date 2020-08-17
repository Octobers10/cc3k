#include "dwarf.h"

using namespace std;

Dwarf::Dwarf(int x, int y):
    Player{100, 20, 30, x, y} {} 


void Dwarf::resetPlayer()  {
    atk = 20;
    def = 30;
}

bool Dwarf::setGold(Gold & gold)  {
    if (gold.getPickable()){
        numGold += 2 * gold.getAmount();
        return true;
    } else {
        return false;
    }
}

void Dwarf::incGold() {
    numGold = numGold + 2;
}

void Dwarf::consumePotion(Potion & potion){
    string type = potion.getType();
    if (type == "RH"){
        if (hp >= 90){
            hp = 100;
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
