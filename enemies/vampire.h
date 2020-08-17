#ifndef _VAMPIRE_H_
#define _VAMPIRE_H_

#include "enemy.h"
#include <string> 

class Vampire: public Enemy {
    public:
    Vampire(int x, int y);
    int notify(std::shared_ptr<Player>the_player, std::string & special) override;
};


#endif
