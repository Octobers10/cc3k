#ifndef _GOBLIN_H_
#define _GOBLIN_H_

#include "enemy.h"

class Goblin: public Enemy {
    public:
    Goblin(int x, int y);
    
    int notify(std::shared_ptr<Player>the_player, std::string & special) override;
};


#endif
