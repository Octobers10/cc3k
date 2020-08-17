#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "character.h"
#include "gold.h"
#include "potion.h"
#include <memory>
#include <vector>

class Enemy;

class Player: public Character {
    protected:
    bool BSuit;
    double numGold; 
    std::vector<bool> knowledge{false, false, false, false, false, false};
    public: 
        Player(int hp, int atk, int def, int x, int y);
        virtual ~Player();
        void wearBSuit();

        //override consumePotion for elves
        virtual void consumePotion(Potion &) = 0;
        //override setGold for dwarf and orc
        virtual bool setGold(Gold &);

        int attackedBy(int);
        int attack(std::shared_ptr<Enemy>);
        virtual void resetPlayer() = 0;
        double getGold();
        virtual void incGold();
        bool stealGold();
        int stealHealth();
        bool getKnowledge(std::string); 
        void setKnowledge(std::string); 
};

#endif
