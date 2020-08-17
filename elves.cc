#include "elves.h"

using namespace std;

Elves::Elves(int x, int y):
    Player{140, 30, 10, x, y} {} 


void Elves::resetPlayer()  {
    atk = 30;
    def = 10;
}

void Elves::consumePotion(Potion & potion)  {
    string type = potion.getType();
    if ((type == "RH") || (type == "PH")){
        if (hp >= 130){
            hp = 140;
        } else{
            hp += 10;
        }
    }
    if ((type == "BA") || (type == "WA")) 
        { atk += 5; }
    if ((type == "BD") || (type == "WD"))
        { def += 5; }
}
