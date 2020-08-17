#include "gold.h"

Gold::Gold(int x, int y, int amount, bool pickable):
    Item{x,y}, amount{amount}, pickable{pickable} {}

Gold::~Gold(){}

void Gold::setPickable(){
    pickable = true;
}

bool Gold::getPickable(){
    return pickable;
}

int Gold::getAmount(){
    return amount; 
}

