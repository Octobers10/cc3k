#ifndef _GOLD_H_
#define _GOLD_H_

#include "item.h"

class Gold: public Item{
    int amount;
    bool pickable; 

    public:
    Gold(int x, int y, int amount, bool pickable=true);
    ~Gold();
    void setPickable() override;
    bool getPickable() override;
    int getAmount();
};


#endif

