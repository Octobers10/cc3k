#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <utility>
#include <string>
#include "direction.h"

class Character {
    protected:
    int hp;
    int atk;
    int def;
    std::pair<int, int> position;
    bool alive; 
    
    public: 
    Character(int hp, int atk, int def, int x, int y);
    virtual ~Character();
    int getHP();
    int getAtk();
    int getDef();
    bool isAlive();
    std::pair<int, int> getPosition();
    void setPosition(int x, int y); 
    void move(Direction);
};

#endif
