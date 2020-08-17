#include "barriersuit.h"

using namespace std;

BarrierSuit::BarrierSuit(int x, int y):
    Item{x,y}, pickable{false} {}


void BarrierSuit::setPickable(){
    pickable = true;
}

bool BarrierSuit::getPickable(){
    return pickable;
}

