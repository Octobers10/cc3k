#include "item.h"

using namespace std;

Item::Item(int x, int y):
    position{make_pair(x,y)} {}

Item::~Item(){}

pair<int, int> Item::getPosition(){
    return position;
}

void Item::setPosition(int x, int y){
    position.first = x;
    position.second = y;
}

void Item::setPickable(){
	return;
}

