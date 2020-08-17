#ifndef _BARRIERSUIT_H_
#define _BARRIERSUIT_H_

#include "item.h"
class BarrierSuit: public Item {
    bool pickable;
    public:
    BarrierSuit(int x, int y);
    bool getPickable() override;
    void setPickable() override;
};


#endif
