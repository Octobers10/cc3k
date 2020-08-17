#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "player.h"

class Human: public Player{
    public:
    Human(int x, int y);
    void resetPlayer() override;
    void consumePotion(Potion &) override;
};

#endif

