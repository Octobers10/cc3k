#include "potion.h"

using namespace std;
Potion::Potion(int x, int y, string type):
    Item{x,y}, type{type} {}

std::string Potion::getType(){
    return type;
}

bool Potion::getPickable(){
	return true;
}
