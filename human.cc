#include "human.h"

using namespace std;

Human::Human(int x, int y):
    Player{140, 20, 20, x, y} {} 



void Human::resetPlayer() {
    atk = 20;
    def = 20;
}


void Human::consumePotion(Potion & potion){
    string type = potion.getType();
    if (type == "RH"){
        if (hp >= 130){
            hp = 140;
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
