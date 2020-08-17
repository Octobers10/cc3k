#ifndef _ELVES_H_
#define _ELVES_H_

#include "player.h"

class Elves: public Player{
    public:
    Elves(int x, int y);
    void consumePotion(Potion &) override;
    void resetPlayer() override;

};

#endif
