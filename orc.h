#ifndef _ORC_H_
#define _ORC_H_

#include "player.h"

class Orc: public Player{
    public:
    Orc(int x, int y);
    void resetPlayer() override;
    bool setGold(Gold &) override;
    void incGold() override;
    void consumePotion(Potion &) override;
};

#endif
