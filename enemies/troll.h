#ifndef _TROLL_H_
#define _TROLL_H_

#include "enemy.h"
#include <memory>

class Troll: public Enemy {
    public:
    Troll(int x, int y);
    int notify(std::shared_ptr<Player>, std::string &) override;
};


#endif
