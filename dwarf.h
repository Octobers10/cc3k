#ifndef _DWARF_H_
#define _DWARF_H_

#include "player.h"

class Dwarf: public Player{
    public:
    Dwarf(int x, int y);
    void resetPlayer() override;
    bool setGold(Gold &) override;
    void incGold() override;
    void consumePotion(Potion &) override;
};

#endif
