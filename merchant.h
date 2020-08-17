#ifndef _MERCHANT_H_
#define _MERCHANT_H_

#include "enemy.h"

class Merchant: public Enemy {
    public:
    Merchant(int x, int y);
    void notify_merchant() override;

};


#endif
